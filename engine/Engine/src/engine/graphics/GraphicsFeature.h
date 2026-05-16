#pragma once

#include "core/feature/Feature.h"
#include "texture/TextureAtlasLoader.h"

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
        ResourceManager& resourceManager;
        IntrusivePointer<TextureAtlasLoader> textureAtlasLoader;

        void uninitGraphicsFeature();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        GraphicsFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~GraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }
    };
}
