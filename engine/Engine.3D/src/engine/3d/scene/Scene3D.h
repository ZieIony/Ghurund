#pragma once

#include "Entity3D.h"

#include "core/resource/Resource.h"
#include "engine/3d/IGraphics3DContext.h"
#include "camera/Camera3D.h"
#include <engine/game/GameObjectDrawCollection.h>
#include <engine/game/GameObjectUpdateCollection.h>

namespace Ghurund::Engine::_3D {
    class Scene3D:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene3D::GET_TYPE();
#pragma endregion

    private:
        IGraphics3DContext& context;
        Camera3D* camera = nullptr;
        GameObjectUpdateCollection& gameObjectsUpdate;
        GameObjectDrawCollection gameObjectsDraw;
        List<IntrusivePointer<Entity3D>> entities;

    public:
        Scene3D(
            IGraphics3DContext& context,
            GameObjectUpdateCollection& gameObjectsUpdate
        ):context(context), gameObjectsUpdate(gameObjectsUpdate) {
        }

        ~Scene3D() {
            if (camera)
                camera->release();
            for (auto& entity : entities) {
                gameObjectsUpdate.remove(entity);
                gameObjectsDraw.remove(entity);
            }
        }

        inline Camera3D* getCamera() const {
            return camera;
        }

        inline void setCamera(Camera3D* camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera3D* Camera;

        inline void add(IntrusivePointer<Entity3D> entity) {
            entities.add(entity);
            gameObjectsDraw.add(entity);
            gameObjectsUpdate.add(entity);
        }

        inline void draw(RenderGroup& rg) {
            gameObjectsDraw.draw(rg);
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene3D::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}