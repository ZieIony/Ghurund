#include "ghpch.h"
#include "Renderer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/ReadOnlyProperty.h"
#include "core/directx/MathTypes.h"

namespace Ghurund {
    const Ghurund::Core::Type& Renderer::GET_TYPE() {
        static auto PROPERTY_CLEARCOLOR = Property<Renderer, const XMFLOAT4*>("ClearColor", (XMFLOAT4 * (Renderer::*)()) & getClearColor, (void(Renderer::*)(const XMFLOAT4*)) & setClearColor);
        static auto PROPERTY_STATISTICS = ReadOnlyProperty<Renderer, RenderingStatistics&>("Statistics", (RenderingStatistics & (Renderer::*)()) & getStatistics);

        static const auto CONSTRUCTOR = Constructor<Renderer>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Renderer>("Ghurund", "Renderer")
            .withProperty(PROPERTY_CLEARCOLOR)
            .withProperty(PROPERTY_STATISTICS)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Renderer::init(Graphics& graphics, ParameterManager& parameterManager) {
        this->graphics = &graphics;
        this->parameterManager = &parameterManager;

        /*for(int i = 0; i<FRAME_COUNT; i++) {
            postprocessRenderTarget[i] = ghnew RenderTarget();
            postprocessRenderTarget[i]->init(*graphics, window.Width, window.Height, DXGI_FORMAT_B8G8R8A8_UNORM);
        }*/

        //lightPassMaterial = Materials::makeLightPass(resourceManager, resourceContext);
        //fullScreenQuad = Models::makeQuad(resourceContext, *lightPassMaterial);
    }

    void Renderer::uninit() {
        /*for(int i = 0; i<FRAME_COUNT; i++) {
            delete postprocessRenderTarget[i];
            postprocessRenderTarget[i] = nullptr;
        }*/
    }

}