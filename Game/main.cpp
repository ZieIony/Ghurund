#include "net/Client.h"
#include "core/Object.h"
#include "core/Logger.h"
#include <fcntl.h>
#include <process.h>
#include <thread>
#include "application/Application.h"
#include "resource/TextResource.h"
#include "game/Scene.h"
#include "collection/TypeMap.h"
#include "graphics/mesh/QuadMesh.h"
#include "audio/Sound.h"

#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

#pragma comment(lib, "GhurundEngine.lib")

class TestLevel:public Level {
private:
    float rotation = 0;
    Application &app;

public:
    TestLevel(Application &app):app(app) {}

    virtual bool onKeyEvent(KeyEvent &event) override {
        if(event.getAction()==KeyAction::DOWN&&event.getKey()==VK_ESCAPE) {
            PostQuitMessage(0);
            return true;
        }
        return false;
    }

    void init() {
        Ghurund::Camera *camera = ghnew Ghurund::Camera();
        camera->initParameters(app.ParameterManager);

        Camera = camera;

        File sceneFile("test.scene");
        if(sceneFile.Exists) {
            app.ResourceManager.loadAsync<Ghurund::Scene>(app.ResourceContext, "test.scene", [&](Ghurund::Scene *resource, Status result) {
                setScene(resource);
            });
        } else {
            Ghurund::Scene *scene = ghnew Ghurund::Scene();
            Scene = scene;
            scene->Entities.add(camera);
            camera->addReference();
            camera->release();

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
            image->release();

            Shader *shader = app.ResourceManager.load<Shader>(app.ResourceContext, "../shaders/basic.hlsl");
            Material *material = new Material(shader);
            material->Textures.set("diffuse", texture);
            texture->addReference();
            shader->release();
            texture->release();

            Model *model = ghnew Model(mesh, material);
            model->initParameters(app.ParameterManager);
            mesh->release();
            material->release();

            scene->Entities.add(model);
            model->addReference();
            model->release();

            Status result = scene->save(app.ResourceManager, "test.scene", SaveOption::SKIP_IF_EXISTS);
            if(result!=Status::OK)
                Logger::log(_T("failed to save scene\n"));

            scene->release();
        }
    }

    void update() {
        rotation += 0.005f;
        camera->setPositionTargetUp(XMFLOAT3(sin(rotation)*600, 200, cos(rotation)*600), XMFLOAT3(0, 50, 0), XMFLOAT3(0, 1, 0));
        camera->setScreenSize(app.Window.Width, app.Window.Height);
    }

    void uninit() {
        camera->release();
    }
};

class TestApplication:public Application {
private:
    Level *testLevel;

public:
    void init() {
        testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);
    }

    void update() {}

    void uninit() {
        ResourceManager.clear();
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