#include "net/Client.h"
#include "core/Object.h"
#include "core/Logger.h"
#include <fcntl.h>
#include <process.h>
#include <thread>
#include "application/Application.h"
#include "application/ApplicationWindowProc.h"
#include "resource/TextResource.h"
#include "game/Scene.h"
#include "collection/TypeMap.h"
#include "graphics/mesh/QuadMesh.h"

#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

#pragma comment(lib, "GhurundEngine.lib")

namespace Ghurund {
    class Proc:public ApplicationWindowProc {
    private:
        std::shared_ptr<TextResource> textRes;
        static const unsigned int KEY_C = 0x43;

    public:
        Proc(Ghurund::Application &app):ApplicationWindowProc(app) {}

        bool onMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
            if(msg==WM_LBUTTONUP) {
                Logger::log(_T("%s\n"), textRes->getText().getData());
                return true;
            }
            if(msg==WM_RBUTTONUP) {
                Application.ResourceManager.load<TextResource>(String(_T("test.txt")), [&](std::shared_ptr<TextResource> &res, Status result) {
                    Logger::log(_T("loaded file: %s, result: %i\n"), res->FileName.getData(), result);
                    textRes = res;
                });
                return true;
            }
            if(msg==WM_KEYUP&&wParam==KEY_C) {
                /*        class MyListener:public NetworkListener {
                void onDisconnected() {
                PostQuitMessage(0);
                }
                };
                client.setNetworkListener(ghnew MyListener());*/

                Application.Client.connect(SocketProtocol::UDP, 59336, _T("127.0.0.1"));
                Application.Client.send("test", strlen("test")+1);
            }
            return ApplicationWindowProc::onMessage(msg, wParam, lParam);
        }
    };
}

class TestApplication:public Application {
private:
    Level *testLevel;
    float rotation = 0;
    Camera *camera;
    Model *model;

public:
    void init() {
        shared_ptr<CommandList> commandList = ResourceManager.getCommandList();
        commandList->reset();

        camera = ghnew Camera();
        camera->initParameters(ParameterManager);

        shared_ptr<Shader> shader(ghnew Shader());
        shader->load(ResourceManager, "../shaders/basic.hlsl");

        shared_ptr<Texture> texture(ghnew Texture());
        texture->load(ResourceManager, "obj/lamborghini/Lamborginhi Aventador_diffuse.jpeg");

        shared_ptr<Scene> scene(ghnew Ghurund::Scene());
        testLevel = ghnew Level();
        testLevel->scene = scene;
        scene->Entities.add(camera);

        shared_ptr<Mesh> mesh(ghnew Mesh());
        mesh->load(ResourceManager, "obj/lamborghini/Lamborghini_Aventador.obj");

        shared_ptr<Material> material(ghnew Material(shader));
        material->Textures.set("diffuse", texture);

        model = ghnew Model(mesh, material);
        model->initParameters(ParameterManager);
        scene->Entities.add(model);

        commandList->finish();

        LevelManager.setLevel(testLevel);
    }

    void update() {
        rotation += 0.005f;
        camera->setPositionTargetUp(XMFLOAT3(sin(rotation)*600, 200, cos(rotation)*600), XMFLOAT3(0, 50, 0), XMFLOAT3(0, 1, 0));
    }

    void uninit() {
        delete testLevel;
        delete model;
        delete camera;
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Logger::init(LogOutput::SYSTEM_CONSOLE);

    {
		TestApplication application;
        Proc proc(application);
        Settings settings;
        settings.parse(cmdLine);
		application.run(&settings, &proc);
    }

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
    dumpMemoryLeaks();
    ComPtr<IDXGIDebug> debugInterface;
    if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface))))
        debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
#endif

    return 0;
}