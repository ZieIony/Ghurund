#include "Ghurund.Engine.OpenGL.h"

#include "engine/application/GameWindow.h"
#include <engine/opengl/Mesh.h>
#include <engine/opengl/OGlRenderer.h>
#include <engine/opengl/Shader.h>
#include <core/io/DirectoryLibrary.h>

namespace Samples {
    using namespace Ghurund::Engine::OpenGL;

    class SampleWindow:public Ghurund::Engine::GameWindow {
    private:
        Shader shader;
        Mesh mesh;

    public:
        SampleWindow(NotNull<Ghurund::Core::Application> app, NotNull<OGlRenderer> renderer):GameWindow(app) {
            Renderer = &renderer;
        }
        
        void init() {
            shader.init(FilePath(L"resources/shaders/OpenGL/rect.vert"), FilePath(L"resources/shaders/OpenGL/rect.frag"));
            mesh.init();
        }

        virtual void paint() override {
            shader.set();

            GLuint resolutionId = glGetUniformLocation(shader.Id, "resolution");
            glUniform2f(resolutionId, 1024, 768);

            mesh.draw();
        }
    };

    class SampleApplication:public Ghurund::Core::Application {
    private:
        OGlRenderer renderer;
        SampleWindow* window = nullptr;

    public:
        virtual void onInit() override {
            ResourceManager->Libraries->add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
            ResourceManager->Libraries->add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

            window = ghnew SampleWindow(*this, renderer);
            window->init();
            window->closed += [this](Window& window) {
                window.Visible = false;
                quit();
                return true;
            };

            window->Title = _T("Sample UI OpenGL");
            window->Size = { 800, 600 };
            window->Position = { (int)window->DecorationMetrics.Left, (int)window->DecorationMetrics.Top };
            window->Visible = true;
            window->bringToFront();
        }

        virtual void onUninit() override {
            delete window;
            window = nullptr;

            ResourceManager->Libraries->clear();
        }
    };

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
