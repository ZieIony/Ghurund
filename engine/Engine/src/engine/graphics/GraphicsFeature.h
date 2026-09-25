#pragma once

#include "core/feature/Feature.h"
#include "texture/TextureAtlasLoader.h"
#include "engine/resource/IGraphicsResourceFactory.h"
#include "memory/IGPUMemoryManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class GraphicsFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GraphicsFeature::GET_TYPE();
#pragma endregion

    private:
        IntrusivePointer<TextureAtlasLoader> textureAtlasLoader;

        void uninitGraphicsFeature();

    protected:
        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

        virtual IGraphicsResourceFactory& getResourceFactoryInternal() = 0;

    public:
        ResourceManager& resourceManager;
        
        GraphicsFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~GraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }

        inline IGraphicsResourceFactory& getResourceFactory() {
            return getResourceFactoryInternal();
        }

        __declspec(property(get = getResourceFactory)) IGraphicsResourceFactory& ResourceFactory;
    };
}
