#pragma once

#include "core/feature/Feature.h"
#include "engine/resource/IGraphicsResourceFactory.h"

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
        void uninitGraphicsFeature();

    protected:
        class IGraphicsResourceFactory* resourceFactory = nullptr;
        class IGPUMemoryManager* memoryManager = nullptr;
  
        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onDeinit() override;

    public:
        ResourceManager& resourceManager;
        
        GraphicsFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~GraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }

        inline IGraphicsResourceFactory& getResourceFactory() {
            return *resourceFactory;
        }

        __declspec(property(get = getResourceFactory)) IGraphicsResourceFactory& ResourceFactory;

        inline IGPUMemoryManager& getMemoryManager() {
            return *memoryManager;
        }

        __declspec(property(get = getMemoryManager)) IGPUMemoryManager& MemoryManager;
    };
}
