#pragma once

#include "engine/ecs/System.h"
#include "engine/graphics/Camera.h"

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
        class World3D& world;
        Camera* camera = nullptr;

    protected:
        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

    public:
        MaterialVariantType defaultMaterialType = MaterialVariantType::LIT;

        MeshRenderingSystem(World3D& world):world(world) {
        }

        ~MeshRenderingSystem() {
            if (camera)
                camera->release();
        }

        inline void setCamera(Camera* camera) {
            setPointer(this->camera, camera);
        }

        inline Camera* getCamera() const {
            return camera;
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera* Camera;
     
        virtual void queueDraw(RenderingContext& renderingContext) override;
    };
}
