#pragma once

#include "engine/2d/graphics/camera/Camera2D.h"
#include "engine/ecs/System.h"

namespace Ghurund::Engine::_2D {
    class SpriteRenderingSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = SpriteRenderingSystem::GET_TYPE();
#pragma endregion

    private:
        class World2D& world;
        Camera2D* camera = nullptr;
        ParameterManager& parameterManager;

    protected:
        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

    public:
        SpriteRenderingSystem(
            World2D& world,
            ParameterManager& parameterManager
        ):world(world), parameterManager(parameterManager) {
        }

        ~SpriteRenderingSystem() {
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
     
        virtual void queueDraw(RenderingContext& renderingContext) override;
    };
}