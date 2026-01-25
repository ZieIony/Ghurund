#pragma once

#include "core/resource/Resource.h"
#include "engine/entity/camera/Camera.h"
#include "engine/entity/Entity.h"

namespace Ghurund::Engine {
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
        List<IntrusivePointer<Entity>> entities;
        IntrusivePointer<Camera> camera;

    public:
        Scene() {}

        inline void setCamera(Camera* camera) {
            this->camera.set(camera);
            if(camera)
                camera->addReference();
        }

        inline Camera* getCamera() {
            return camera.get();
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera* Camera;

        inline List<IntrusivePointer<Entity>>& getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) List<IntrusivePointer<Entity>>& Entities;

        inline void update(uint64_t time) {
            for (auto& entity : entities)
                entity->update(time);
        }

        inline void draw(RenderGroup& group) {
            for (auto& entity : entities)
                entity->draw(group);
        }
#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}