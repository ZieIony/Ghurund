#include "FileUtils.h"
#include "core/Logger.h"
#include "application/Application.h"
#include "audio/Sound.h"
#include "game/entity/Scene.h"
#include "game/entity/Models.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/Materials.h"
#include "net/Client.h"
#include "resource/TextResource.h"
#include "game/CameraController.h"
#include "game/LevelManager.h"
#include "game/entity/Scenes.h"

#include "core/Allocator.h"

#include <fcntl.h>
#include <process.h>
#include <thread>

#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

#pragma comment(lib, "GhurundEngine.lib")

class TestLevel:public Level {
private:
    Camera *camera = nullptr;
    CameraController *cameraController = nullptr;
    Application &app;
    TransformedEntity *selection = nullptr;
    Material *overrideMaterial = nullptr;
    Scene *scene = nullptr;
    Scene *editorScene = nullptr;
    Material *invalidMaterial = nullptr;

public:
    TestLevel(Application &app):app(app) {}

    virtual bool onMouseButtonEvent(MouseButtonEvent &event) override {
        return cameraController->dispatchMouseButtonEvent(event);
    }

    virtual bool onMouseMouseMotionEvent(MouseMotionEvent &event) override {
        return cameraController->dispatchMouseMotionEvent(event);
    }

    virtual bool onMouseWheelEvent(MouseWheelEvent &event) override {
        return cameraController->dispatchMouseWheelEvent(event);
    }

    virtual bool onKeyEvent(KeyEvent &event) override {
        if(event.Action==KeyAction::DOWN&&event.Key=='W') {
            if(overrideMaterial!=nullptr)
                overrideMaterial->release();
            overrideMaterial = Materials::makeWireframe(app.ResourceManager, app.ResourceContext);
        } else if(event.Action==KeyAction::UP&&event.Key=='W') {
            if(overrideMaterial!=nullptr)
                overrideMaterial->release();
            overrideMaterial = nullptr;
        } else if(event.Action==KeyAction::DOWN&&event.Key=='C') {
            if(overrideMaterial!=nullptr)
                overrideMaterial->release();
            overrideMaterial = Materials::makeChecker(app.ResourceManager, app.ResourceContext);
        } else if(event.Action==KeyAction::UP&&event.Key=='C') {
            if(overrideMaterial!=nullptr)
                overrideMaterial->release();
            overrideMaterial = nullptr;
        } else if(event.Action==KeyAction::DOWN&&event.Key==VK_ESCAPE) {
            PostQuitMessage(0);
            return true;
        }
        return false;
    }

    virtual void onInit() override {
        camera = ghnew Ghurund::Camera();
        camera->initParameters(app.ParameterManager);
        camera->setPositionTargetUp(XMFLOAT3(0, 50, -500), XMFLOAT3(0, 50, 0));

        cameraController = ghnew CameraController(*camera, &app.Window);

        File sceneFile("test/test.scene");
        if(sceneFile.Exists) {
            app.ResourceManager.loadAsync<Ghurund::Scene>(app.ResourceContext, "test/test.scene", [&](Ghurund::Scene *scene, Status result) {
                scene->initParameters(app.ParameterManager);
                this->scene = scene;
                scene->release();
            });
        } else {
            Scene *scene = ghnew Ghurund::Scene();

            Model *model;
            {
                Mesh *mesh;
                File file("test/obj/lamborghini/Lamborghini_Aventador.mesh");
                if(file.Exists) {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, file);
                } else {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, "test/obj/lamborghini/Lamborghini_Aventador.obj");
                    if(mesh!=nullptr)
                        mesh->save(app.ResourceManager, "test/obj/lamborghini/Lamborghini_Aventador.mesh");
                }

                Image *image = app.ResourceManager.load<Image>(app.ResourceContext, "test/obj/lamborghini/Lamborginhi Aventador_diffuse.jpeg");
                if(image!=nullptr&&mesh!=nullptr) {
                    Texture *texture = ghnew Texture();
                    texture->init(app.ResourceContext, *image);

                    Shader *shader = app.ResourceManager.load<Shader>(app.ResourceContext, "shaders/basic.hlsl");
                    Material *material = ghnew Material(shader);
                    material->Textures.set("diffuse", texture);
                    material->Valid = true;
                    texture->release();

                    model = ghnew Model(mesh, material);
                    model->Valid = true;
                    mesh->release();
                    material->release();

                    scene->Entities.add(model);
                    model->release();
                }
            }

            /*{
                Material *material = Materials::makeChecker(app.ResourceManager, app.ResourceContext);
                TransformedEntity *transformedModel = Models::makeSphere(app.ResourceContext, *material);
                material->release();

                transformedModel->Position = XMFLOAT3(100, 100, 100);
                transformedModel->Scale = XMFLOAT3(50, 50, 50);

                scene->Entities.add(transformedModel);
                transformedModel->release();
            }*/

            /*{
                Material *material = Materials::makeWireframe(app.ResourceManager, app.ResourceContext);
                TransformedEntity *selection = Models::makeCube(app.ResourceContext, *material);
                material->release();

                selection->Position = model->Mesh->BoundingBox.Center;
                selection->Scale = model->Mesh->BoundingBox.Extents;

                scene->Entities.add(selection);
                selection->release();
            }*/

            Status result = scene->save(app.ResourceManager, "test/test.scene", SaveOption::SKIP_IF_EXISTS);
            if(result!=Status::OK)
                Logger::log(_T("failed to save scene\n"));

            scene->initParameters(app.ParameterManager);
            scene->release();
            this->scene = scene;
        }

        invalidMaterial = Materials::makeInvalid(app.ResourceManager, app.ResourceContext);
        editorScene = Scenes::makeEditor(app.ResourceManager, app.ResourceContext);
    }

    virtual void onPreDraw(RenderStep &step) {
        GlobalEntity<Model> *model = step.pick(app.Input.MousePos);
        if(model!=nullptr) {
            //          selection->Position = model->BoundingBox.Center;
          //            selection->Scale = model->BoundingBox.Extents;
        }
    }

    virtual void onUpdate() override {
        camera->setScreenSize(app.Window.Width, app.Window.Height);
    }

    virtual void onDraw(Renderer &renderer, ParameterManager &parameterManager) override {
        if(scene!=nullptr)
            renderer.draw(*camera, *scene, parameterManager, nullptr, invalidMaterial);
        renderer.draw(*camera, *editorScene, parameterManager, nullptr, invalidMaterial);
    }

    virtual void onUninit() override {
        camera->release();
        scene->release();
        editorScene->release();
        invalidMaterial->release();
        delete cameraController;
    }
};

class TestApplication:public Application {
private:
    Level *testLevel = nullptr;

public:
    void onInit() {
        testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);

        Renderer.ClearColor = ghnew XMFLOAT4(makeColor(0xff000000));
    }

    void onUninit() {
        LevelManager.setLevel(nullptr);
        delete testLevel;
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    Logger::init(LogOutput::SYSTEM_CONSOLE);

    {
        TestApplication application;
        Settings settings;
        settings.parse(cmdLine);
        application.run(&settings);
    }

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
    ComPtr<IDXGIDebug> debugInterface;
    if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface))))
        debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
#endif
    return 0;
}