#pragma once

#include "Ghurund.Engine.OpenGL.h"

#include "engine/application/GameWindow.h"
#include <engine/opengl/mesh/OglMesh.h>
#include <engine/opengl/OGlRenderer.h>
#include <engine/opengl/shader/OglShader.h>
#include <engine/opengl/shader/OglShaderLoader.h>
#include <engine/graphics/mesh/QuadMesh.h>

namespace Samples {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;

    class SampleWindow:public Ghurund::Engine::GameWindow {
    private:
        OglShaderCompiler shaderCompiler;
        IntrusivePointer<OglShaderLoader> shaderLoader = makeIntrusive<OglShaderLoader>(shaderCompiler);
        IntrusivePointer<OglShader> shader;
        IntrusivePointer<OglMesh> mesh = makeIntrusive<OglMesh>();
        IntrusivePointer<QuadMesh> quadMesh = makeIntrusive<QuadMesh>();

    public:
        SampleWindow(NotNull<Ghurund::Core::Application> app, NotNull<OglRenderer> renderer):GameWindow(app) {
            Renderer = &renderer;
            app->ResourceManager->Loaders->set<OglShader>(shaderLoader.get());
        }

        void init() {
            shader = IntrusivePointer<OglShader>(Application->ResourceManager->load<OglShader>(FilePath(L"rect.shader"), DirectoryPath(L"./resources/shaders/OpenGL")));
            mesh = makeIntrusive<OglMesh>();
            quadMesh->init();
            mesh->init(quadMesh.get());
        }

        virtual void paint() override {
            shader->set();

            GLuint resolutionId = glGetUniformLocation(shader->Id, "resolution");
            glUniform2f(resolutionId, 1024, 768);

            mesh->draw();
        }
    };
}
