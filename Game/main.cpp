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
    shared_ptr<Model> model;
    Parameter *parameter;

public:
    void init() {
        Material material;
        material.FileName = String(_T("material.mtr"));
        shared_ptr<Shader> shader(ghnew Shader());
        material.Shader = shader;
        shader->FileName = _T("shader.shd");
        File file(_T("shader.vs.hlsl"));
        file.read();
        ASCIIString sourceCode;
        sourceCode.add((const char *)file.Data, file.Size);
        shader->setSourceCode(sourceCode.getData());
        shader->compile();
        shader->save(ResourceManager);
        material.save(ResourceManager);

        XMFLOAT4 value = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
        parameter = ParameterManager.add("globalColor", sizeof(value));
        parameter->setValue(&value);

        shared_ptr<Scene> scene(ghnew Ghurund::Scene());
        Level *testLevel = ghnew Level();
        testLevel->scene = scene;
        shared_ptr<Camera> camera(ghnew Camera());
        camera->initParameters(ParameterManager);
        scene->addCamera(camera);

        model = shared_ptr<Model>(ghnew Model());
        shared_ptr<CommandList> commandList = ResourceManager.getCommandList();
        commandList->reset();
        if(Status::OK==model->init(ResourceManager)) {
            testLevel->scene->addModel(model);
        }
        commandList->finish();

        LevelManager.changeLevel(testLevel);
    }

    void uninit() {
        delete testLevel;
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Logger::init(LogOutput::CUSTOM_CONSOLE);

    {
        TestApplication application;
        Proc proc(application);
        Settings settings;
        tchar *cmdLineCopy = toTchar(cmdLine);
        settings.parse(String(cmdLineCopy));
        delete[] cmdLineCopy;
        application.run(&settings, &proc);
    }

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
    dumpMemoryLeaks();
    ComPtr<IDXGIDebug> debugInterface;
    if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface)))) {
        debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
    }
#endif

    return 0;
}