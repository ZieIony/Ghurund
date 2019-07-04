#include "Ghurund.h"
#include "game/sky/AdvancedSky.h"

using namespace Ghurund;
using namespace DirectX;

class TestLevel :public Level {
private:
    Camera* camera = nullptr;
    CameraController* cameraController = nullptr;
    Application& app;
    Material* wireframeMaterial = nullptr, * outlineMaterial = nullptr, * checkerMaterial = nullptr;
    ScopedPointer<AdvancedSky> sky;

    RenderStep editorStep, sceneStep, selectionStep;

public:
    TestLevel(Application& app) :app(app) {}

    virtual bool onMouseButtonEvent(MouseButtonEventArgs& event) override {
        /*if (event.Action == MouseAction::DOWN) {
            Model* model = sceneStep.pick(app.Input.MousePos);
            if (model != nullptr)
                return true;
        }*/
        return cameraController->dispatchMouseButtonEvent(event);
    }

    virtual bool onMouseMouseMotionEvent(MouseMotionEventArgs& event) override {
        return cameraController->dispatchMouseMotionEvent(event);
    }

    virtual bool onMouseWheelEvent(MouseWheelEventArgs& event) override {
        return cameraController->dispatchMouseWheelEvent(event);
    }

    virtual bool onKeyEvent(KeyEventArgs& event) override {
        if (event.Action == KeyAction::DOWN && event.Key == VK_ESCAPE) {
            PostQuitMessage(0);
            return true;
        }
        return false;
    }

    virtual void onInit() override {
        ScopedPointer<ValueParameter> lightPosParameter = ghnew ValueParameter("lightPos", ParameterType::FLOAT3);
        app.ParameterManager.Parameters.add(lightPosParameter);
        XMFLOAT3 lightPos = { sin(app.Timer.Time) * 150, 150, cos(app.Timer.Time) * 150 };
        lightPosParameter->setValue(&lightPos);

        camera = ghnew Ghurund::Camera();
        camera->setPositionTargetUp({ 2000, 380, -500 }, { 0, 180, 0 });
        camera->initParameters(app.ParameterManager);

        cameraController = ghnew CameraController(*camera, &app.Window);

        wireframeMaterial = Materials::makeWireframe(app.ResourceContext);
        outlineMaterial = Materials::makeOutline(app.ResourceContext);
        checkerMaterial = Materials::makeChecker(app.ResourceContext);

        File sceneFile("test/test.scene");
        /*if (sceneFile.Exists) {
            app.ResourceManager.loadAsync<Ghurund::Scene>(app.AsyncResourceContext, "test/test.scene", [&](Ghurund::Scene* scene, Status result) {
                if (result != Status::OK)
                    return;
                scene->initParameters(app.ParameterManager);
                sceneStep.Entities.add(scene);
                selectionStep.Entities.add(scene->Entities[0]);
                scene->release();
                });
        } else {*/
        ScopedPointer<Scene> scene = makeScene();
        sceneStep.Entities.add(scene);
        //selectionStep.Entities.add(scene->Entities[0]);

        /*Status result = scene->save(app.ResourceContext, "test/test.scene", SaveOption::SKIP_IF_EXISTS);
        if (result != Status::OK)
            Logger::log(LogType::WARNING, _T("failed to save scene\n"));*/
            //}

        editorStep.Camera = camera;
        ScopedPointer<Scene> editorScene = Scenes::makeEditor(app.ResourceContext);
        editorStep.Entities.add(editorScene);
        editorStep.initParameters(app.ParameterManager);
        app.Renderer.Steps.add(&editorStep);

        selectionStep.Camera = camera;
        ScopedPointer<Scene> selectionScene = ghnew Scene();
        selectionStep.Entities.add(selectionScene);
        selectionStep.initParameters(app.ParameterManager);
        selectionStep.OverrideMaterial = outlineMaterial;
        app.Renderer.Steps.add(&selectionStep);

        sceneStep.Camera = camera;
        ScopedPointer<Material> invalidMaterial = Materials::makeInvalid(app.ResourceContext);
        sceneStep.InvalidMaterial = invalidMaterial;
        sceneStep.initParameters(app.ParameterManager);
        app.Renderer.Steps.add(&sceneStep);

        const char* sourceCode = "void main(Camera &camera){camera.setOrbit(timer.getTime(),cos(timer.getTime()/5.0f)*3.0f+30);}";
        ScopedPointer<Script> script = Scripts::make(camera, sourceCode);

        app.ScriptEngine.Scripts.add(script);
    }

    Scene* makeScene() {
        /*ScopedPointer<Model> lamborghini;
        {
            ScopedPointer<Mesh> mesh;
            File file("test/obj/lamborghini/Lamborghini_Aventador.mesh");
            if (file.Exists) {
                mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, file);
            } else {
                mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, "test/obj/lamborghini/Lamborghini_Aventador.obj");
                if (mesh != nullptr)
                    mesh->save(app.ResourceContext, file);
            }

            ScopedPointer<Texture> diffuseTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/lamborghini/Lamborginhi Aventador_diffuse.jpeg");
            ScopedPointer<Texture> specularTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/lamborghini/Lamborginhi Aventador_spec.jpeg");
            ScopedPointer<Texture> normalTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/house/house_normal.png");
            if (diffuseTexture != nullptr && specularTexture != nullptr && mesh != nullptr) {
                ScopedPointer<Material> material = Materials::makeBasicLight(app.ResourceContext, diffuseTexture, specularTexture, normalTexture);

                lamborghini = ghnew Model(mesh, material);
                lamborghini->Name = "lamborghini";
                lamborghini->Valid = true;
            }
        }*/

        ScopedPointer<Model> house;
        {
            ScopedPointer<Mesh> mesh;
            File file("test/obj/house/house.mesh");
            if (file.Exists) {
                mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, file);
            }
            else {
                mesh = app.ResourceManager.load<Mesh>(app.ResourceContext, "test/obj/house/house_obj.obj");
                if (mesh != nullptr)
                    mesh->save(app.ResourceContext, file);
            }

            ScopedPointer<Texture> diffuseTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/house/house_diffuse.png");
            ScopedPointer<Texture> specularTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/house/house_spec.png");
            ScopedPointer<Texture> normalTexture = Textures::makeFromImage(app.ResourceContext, "test/obj/house/house_normal.png");
            if (diffuseTexture != nullptr && specularTexture != nullptr && normalTexture != nullptr && mesh != nullptr) {
                ScopedPointer<Material> material = Materials::makeBasicLight(app.ResourceContext, diffuseTexture, specularTexture, normalTexture);

                house = ghnew Model(mesh, material);
                house->Name = "house";
                house->Valid = true;
            }
        }

        ScopedPointer<Model> cone;
        {
            ScopedPointer<Material> material = Materials::makeNormals(app.ResourceContext);
            cone = Models::makeCone(app.ResourceContext, *material);

            cone->Name = "cone";
            cone->Position = { 100, 100, 100 };
            cone->Scale = { 50, 100, 50 };
        }

        ScopedPointer<Model> light;
        {
            ScopedPointer<Material> material = Materials::makeNormals(app.ResourceContext);
            light = Models::makeSphere(app.ResourceContext, *material);

            light->Name = "light";
            light->Position = { 120, 100, -150 };
            light->Scale = { 10, 10, 10 };
        }

        sky = ghnew AdvancedSky();
        sky->init(app.ResourceContext, camera);

        return ghnew Scene({ house, sky });
    }

    virtual void onUpdate() override {
        ValueParameter* param = (ValueParameter*)app.ParameterManager.getParameter("lightPos");
        XMFLOAT3 lightPos = { sin(app.Timer.Time) * 150, 150, cos(app.Timer.Time) * 150 };
        param->setValue(&lightPos);

        sky->SunDirection = { 1, sin(app.Timer.Time / 10), cos(app.Timer.Time / 10) };

        camera->ScreenSize = app.Window.Size;
        cameraController->update(app.Input, app.Timer.FrameTime);
    }

    virtual void onUninit() override {
        camera->release();
        wireframeMaterial->release();
        outlineMaterial->release();
        checkerMaterial->release();
        delete cameraController;
    }
};
