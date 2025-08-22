#include "Ghurund.Engine.OpenGL.h"

#include "engine/application/GameWindow.h"
#include <engine/opengl/mesh/OglMesh.h>
#include <engine/opengl/OGlRenderer.h>
#include <engine/opengl/shader/OglShader.h>
#include <core/io/DirectoryLibrary.h>
#include <engine/opengl/shader/OglShaderLoader.h>
#include <engine/graphics/mesh/QuadMesh.h>

namespace Samples {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;

    class SampleWindow:public Ghurund::Engine::GameWindow {
    private:
        OglShaderCompiler shaderCompiler;
        OglShaderLoader shaderLoader = shaderCompiler;
        IntrusivePointer<OglShader> shader;
        IntrusivePointer<OglMesh> mesh;
        QuadMesh quadMesh;

    public:
        SampleWindow(NotNull<Ghurund::Core::Application> app, NotNull<OglRenderer> renderer):GameWindow(app) {
            Renderer = &renderer;
            app->ResourceManager->Loaders->set<OglShader>(shaderLoader);
        }
        
        void init() {
            shader = IntrusivePointer<OglShader>(Application->ResourceManager->load<OglShader>(FilePath(L"resources/shaders/OpenGL/rect.glsl"), DirectoryPath()));
            mesh = makeIntrusive<OglMesh>();
            quadMesh.init();
            mesh->init(quadMesh);
        }

        virtual void paint() override {
            shader->set();

            GLuint resolutionId = glGetUniformLocation(shader->Id, "resolution");
            glUniform2f(resolutionId, 1024, 768);

            mesh->draw();
        }
    };

    class SampleApplication:public Ghurund::Core::Application {
    private:
        OglRenderer* renderer = nullptr;
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
