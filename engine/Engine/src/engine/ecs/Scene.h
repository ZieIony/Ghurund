#pragma once

#include "core/resource/Resource.h"
#include "engine/ecs/Entity.h"
#include "core/concepts/Derived.h"
#include "engine/graphics/Camera.h"

#include <entt.hpp>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class Scene:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene::GET_TYPE();
#pragma endregion

    private:
        Camera* camera = nullptr;

    public:
        entt::registry entityRegistry;	// TODO: fix getView<>() and make entityRegistry private

        ~Scene() {
            if (camera)
                camera->release();
            entityRegistry.clear();
        }

        void init();

        inline Camera* getCamera() const {
            return camera;
        }

        inline void setCamera(Camera* camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera* Camera;

        template<Derived<Entity> T>
        inline T spawnEntity() {
            return T(entityRegistry, entityRegistry.create());
        }

        inline void destroyEntity(Entity& entity) {
            entityRegistry.destroy(entity.Id);
        }

        // TODO: why this doesn't work?
        template<typename... T>
        [[nodiscard]]
        inline auto getView() const {
            return entityRegistry.view<T...>();
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD, 1);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion
    };
}
