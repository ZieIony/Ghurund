#include "net/Client.h"
#include "core/Logger.h"
#include <fcntl.h>
#include <process.h>
#include <thread>
#include "application/Application.h"
#include "resource/TextResource.h"
#include "game/Scene.h"
#include "graphics/mesh/QuadMesh.h"
#include "audio/Sound.h"
#include "graphics/Models.h"
#include "graphics/Materials.h"

#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

#pragma comment(lib, "GhurundEngine.lib")

class TestLevel:public Level {
private:
    float yaw = 0, pitch = 0;
    Application &app;
    bool pressed = false;
    TransformedEntity *selection;

public:
    TestLevel(Application &app):app(app) {}

    virtual bool onMouseButtonEvent(MouseButtonEvent &event) override {
        if(event.Action==MouseAction::DOWN&&event.Button==MouseButton::LEFT) {
            pressed = true;
            SetCapture(app.Window.Handle);
        } else if(event.Action==MouseAction::UP&&event.Button==MouseButton::LEFT) {
            pressed = false;
            ReleaseCapture();
        }
        return true;
    }

    virtual bool onMouseMouseMotionEvent(MouseMotionEvent &event) override {
        if(pressed) {
            yaw = event.Delta.x/5.0f;
            pitch = -event.Delta.y/5.0f;
        }
        return true;
    }

    virtual bool onKeyEvent(KeyEvent &event) override {
        if(event.Action==KeyAction::DOWN&&event.Key==VK_ESCAPE) {
            PostQuitMessage(0);
            return true;
        }
        return false;
    }

    virtual void onInit() override {
        Ghurund::Camera *camera = ghnew Ghurund::Camera();
        camera->initParameters(app.ParameterManager);
        camera->setPositionTargetUp(XMFLOAT3(0, 50, -500), XMFLOAT3(0, 50, 0));

        Camera = camera;

        File sceneFile("test.scene");
        /*if(sceneFile.Exists) {
            app.ResourceManager.loadAsync<Ghurund::Scene>(app.ResourceContext, "test.scene", [&](Ghurund::Scene *scene, Status result) {
                setScene(scene);
                scene->initParameters(app.ParameterManager);
            });
        } else {*/
            Ghurund::Scene *scene = ghnew Ghurund::Scene();
            Scene = scene;
            scene->Entities.add(camera);
            camera->release();

            Model *model;
            {
                Mesh *mesh;
                File file("obj/lamborghini/Lamborghini_Aventador.mesh");
                if(file.Exists) {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, file);
                } else {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, "obj/lamborghini/Lamborghini_Aventador.obj");
                    mesh->save(app.ResourceManager, "obj/lamborghini/Lamborghini_Aventador.mesh");
                }

                Image *image = app.ResourceManager.load<Image>(app.ResourceContext, "obj/lamborghini/Lamborginhi Aventador_diffuse.jpeg");
                Texture *texture = ghnew Texture();
                texture->init(app.ResourceContext, *image);

                Shader *shader = app.ResourceManager.load<Shader>(app.ResourceContext, "../shaders/basic.hlsl");
                Material *material = ghnew Material(shader);
                material->Textures.set("diffuse", texture);
                material->Valid = true;
                texture->release();

                model = ghnew Model(mesh, material);
                model->Valid = true;
                material->release();

                scene->Entities.add(model);
                model->release();
            }

            {
                Material *material = Materials::makeChecker(app.ResourceManager, app.ResourceContext);
                TransformedEntity *transformedModel = Models::makeSphere(app.ResourceContext, *material);
                material->release();

                transformedModel->Position = XMFLOAT3(100, 100, 100);
                transformedModel->Scale = XMFLOAT3(50, 50, 50);

                //scene->Entities.add(transformedModel);
                transformedModel->release();
            }

            {
                Material *material = Materials::makeWireframe(app.ResourceManager, app.ResourceContext);
                TransformedEntity *transformedModel = Models::makePlane(app.ResourceContext, *material);
                material->release();

                transformedModel->Scale = XMFLOAT3(10000, 1, 10000);

                //scene->Entities.add(transformedModel);
                transformedModel->release();
            }

            {
                Material *material = Materials::makeWireframe(app.ResourceManager, app.ResourceContext);
                TransformedEntity *selection = Models::makeCube(app.ResourceContext, *material);
                material->release();
         
                selection->Position = model->Mesh->BoundingBox.Center;
                selection->Scale = model->Mesh->BoundingBox.Extents;

                scene->Entities.add(selection);
                selection->release();
            }

            /*Status result = scene->save(app.ResourceManager, "test.scene");
            if(result!=Status::OK)
                Logger::log(_T("failed to save scene\n"));*/

     
            scene->initParameters(app.ParameterManager);
            scene->release();
        //}
    }

    virtual void onPreDraw(RenderingBatch &batch) {
        GlobalEntity<Model> *model = batch.pick(*camera, app.Input.MousePos);
        if(model!=nullptr) {
  //          selection->Position = model->BoundingBox.Center;
//            selection->Scale = model->BoundingBox.Extents;
        }
    }

    virtual void onUpdate() override {
        if(app.Input.Keys[VK_CONTROL]) {
            camera->rotate(yaw*XM_PI/180, pitch*XM_PI/180);
        } else {
            camera->orbit(yaw*XM_PI/180, pitch*XM_PI/180);
        }
        yaw = 0;
        pitch = 0;
        camera->setScreenSize(app.Window.Width, app.Window.Height);
    }

    virtual void onUninit() override {
    }
};

class TestApplication:public Application {
private:
    Level *testLevel;

public:
    void onInit() {
        testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);
    }

    void onUpdate() {}

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