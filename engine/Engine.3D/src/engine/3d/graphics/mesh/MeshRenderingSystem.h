#pragma once

#include "engine/3d/graphics/camera/Camera3D.h"
#include "engine/ecs/System.h"

namespace Ghurund::Engine {
    class World;
}

namespace Ghurund::Engine::_3D {
    class MeshRenderingSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = MeshRenderingSystem::GET_TYPE();
#pragma endregion

    private:
        World& world;
        Camera3D* camera = nullptr;
        ParameterManager& parameterManager;

    protected:
        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

    public:
        MeshRenderingSystem(
            World& world,
            ParameterManager& parameterManager
        ):world(world), parameterManager(parameterManager) {
        }

        ~MeshRenderingSystem() {
            if (camera)
                camera->release();
        }

        inline void setCamera(Camera3D* camera) {
            setPointer(this->camera, camera);
        }

        inline Camera3D* getCamera() const {
            return camera;
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera3D* Camera;
     
        virtual void queueDraw(RenderingContext& renderingContext) override;
    };
}