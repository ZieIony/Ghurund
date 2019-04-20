#include "FileUtils.h"
#include "core/Logger.h"
#include "core/ScopedPointer.h"
#include "application/Application.h"
#include "audio/Sound.h"
#include "game/entity/Scene.h"
#include "game/entity/Models.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/Materials.h"
#include "net/Client.h"
#include "game/CameraController.h"
#include "game/LevelManager.h"
#include "game/entity/Scenes.h"
#include "script/Scripts.h"

#include <fcntl.h>
#include <process.h>
#include <thread>

#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

class TestLevel:public Level {
private:
    Camera* camera = nullptr;
    CameraController* cameraController = nullptr;
    Application& app;
    Entity* selection = nullptr;
    Material* overrideMaterial = nullptr;
    Material* invalidMaterial = nullptr;

    RenderStep editorStep, sceneStep;

public:
    TestLevel(Application& app):app(app) {}

    virtual bool onMouseButtonEvent(MouseButtonEvent& event) override {
        if (event.Action == MouseAction::DOWN) {
            Model* model = sceneStep.pick(app.Input.MousePos);
            if (model != nullptr)
                return true;
        }
        return cameraController->dispatchMouseButtonEvent(event);
    }

    virtual bool onMouseMouseMotionEvent(MouseMotionEvent& event) override {
        return cameraController->dispatchMouseMotionEvent(event);
    }

    virtual bool onMouseWheelEvent(MouseWheelEvent& event) override {
        return cameraController->dispatchMouseWheelEvent(event);
    }

    virtual bool onKeyEvent(KeyEvent& event) override {
        if (event.Action == KeyAction::DOWN && event.Key == 'W') {
            if (overrideMaterial != nullptr)
                overrideMaterial->release();
            overrideMaterial = Materials::makeWireframe(app.ResourceManager, app.ResourceContext);
        } else if (event.Action == KeyAction::UP && event.Key == 'W') {
            if (overrideMaterial != nullptr)
                overrideMaterial->release();
            overrideMaterial = nullptr;
        } else if (event.Action == KeyAction::DOWN && event.Key == 'C') {
            if (overrideMaterial != nullptr)
                overrideMaterial->release();
            overrideMaterial = Materials::makeChecker(app.ResourceManager, app.ResourceContext);
        } else if (event.Action == KeyAction::UP && event.Key == 'C') {
            if (overrideMaterial != nullptr)
                overrideMaterial->release();
            overrideMaterial = nullptr;
        } else if (event.Action == KeyAction::DOWN && event.Key == VK_ESCAPE) {
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

        editorStep.Camera = camera;
        editorStep.initParameters(app.ParameterManager);
        app.Renderer.Steps.add(&editorStep);

        sceneStep.Camera = camera;
        sceneStep.initParameters(app.ParameterManager);
        app.Renderer.Steps.add(&sceneStep);

        File sceneFile("test/test.scene");
        if (sceneFile.Exists) {
            app.ResourceManager.loadAsync<Ghurund::Scene>(app.AsyncResourceContext, "test/test.scene", [&](Ghurund::Scene * scene, Status result) {
                if (result != Status::OK)
                    return;
                scene->initParameters(app.ParameterManager);
                sceneStep.Entities.add(scene);
                scene->release();
                });
        } else {
            ScopedPointer<Scene> scene = ghnew Ghurund::Scene();

            {
                ScopedPointer<Mesh> mesh;
                File file("test/obj/lamborghini/Lamborghini_Aventador.mesh");
                if (file.Exists) {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, file);
                } else {
                    mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, "test/obj/lamborghini/Lamborghini_Aventador.obj");
                    if (mesh != nullptr)
                        mesh->save(app.ResourceManager, app.ResourceContext, "test/obj/lamborghini/Lamborghini_Aventador.mesh");
                }

                ScopedPointer<Image> image = app.ResourceManager.load<Image>(app.ResourceContext, "test/obj/lamborghini/Lamborginhi Aventador_diffuse.jpeg");
                if (image != nullptr && mesh != nullptr) {
                    ScopedPointer<Texture> texture = ghnew Texture();
                    texture->init(app.ResourceContext, *image);

                    ScopedPointer<Shader> shader = app.ResourceManager.load<Shader>(app.ResourceContext, "shaders/basic.hlsl");
                    ScopedPointer<Material> material = ghnew Material(shader);
                    material->Textures.set("diffuse", texture);
                    material->Valid = true;

                    ScopedPointer<Model> model = ghnew Model(mesh, material);
                    model->Valid = true;

                    scene->Entities.add(model);
                }
            }

            /*{
            Material *material = Materials::makeNormals(app.ResourceManager, app.ResourceContext);
            TransformedEntity *transformedModel = Models::makeCone(app.ResourceContext, *material);
            material->release();

            //transformedModel->Position = XMFLOAT3(100, 100, 100);
            transformedModel->Scale = XMFLOAT3(50, 100, 50);

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

            Status result = scene->save(app.ResourceManager, app.ResourceContext, "test/test.scene", SaveOption::SKIP_IF_EXISTS);
            if (result != Status::OK)
                Logger::log(LogType::WARNING, _T("failed to save scene\n"));

            scene->initParameters(app.ParameterManager);
            sceneStep.Entities.add(scene);
        }

        invalidMaterial = Materials::makeInvalid(app.ResourceManager, app.ResourceContext);
        ScopedPointer<Scene> editorScene = Scenes::makeEditor(app.ResourceManager, app.ResourceContext);
        editorStep.Entities.add(editorScene);

        const char* sourceCode = "void main(Camera &camera){camera.setOrbit(timer.getTime(),cos(timer.getTime()/5.0f)*3.0f+30);}";
        ScopedPointer<Script> script = Scripts::make(camera, sourceCode);

        app.ScriptEngine.Scripts.add(script);
    }

    virtual void onUpdate() override {
        camera->setScreenSize(app.Window.Width, app.Window.Height);
    }

    virtual void onUninit() override {
        camera->release();
        if (invalidMaterial)
            invalidMaterial->release();
        delete cameraController;
    }
};
