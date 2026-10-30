#pragma once

#include "engine/2d/scene/camera/Camera2D.h"
#include "engine/ecs/System.h"

namespace Ghurund::Engine {
    class World;
}

namespace Ghurund::Engine::_2D {
    class VisualizationRenderingSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = VisualizationRenderingSystem::GET_TYPE();
#pragma endregion

    private:
        World& world;
        Camera2D* camera = nullptr;
        ParameterManager& parameterManager;

    protected:
        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

    public:
        VisualizationRenderingSystem(
            World& world,
            ParameterManager& parameterManager
        ):world(world), parameterManager(parameterManager) {
        }

        ~VisualizationRenderingSystem() {
            if (camera)
                camera->release();
        }

        inline void setCamera(Camera2D* camera) {
            setPointer(this->camera, camera);
        }

        inline Camera2D* getCamera() const {
            return camera;
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera2D* Camera;

        virtual void update(const Timer& timer);

        virtual void queueDraw(RenderingContext& renderingContext) override;
    };
}
