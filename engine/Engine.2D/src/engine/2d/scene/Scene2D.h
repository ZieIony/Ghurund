#pragma once

#include "Entity2D.h"

#include "core/resource/Resource.h"
#include "engine/2d/IGraphics2DContext.h"
#include "camera/Camera2D.h"
#include <engine/game/GameObjectDrawCollection.h>
#include <engine/game/GameObjectUpdateCollection.h>

namespace Ghurund::Engine::_2D {
    class Scene2D:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene2D::GET_TYPE();
#pragma endregion

    private:
        IGraphics2DContext& context;
        Camera2D* camera = nullptr;
        GameObjectUpdateCollection& gameObjectsUpdate;
        GameObjectDrawCollection gameObjectsDraw;
        List<IntrusivePointer<Entity2D>> entities;

    public:
        Scene2D(
            IGraphics2DContext& context,
            GameObjectUpdateCollection& gameObjectsUpdate
		):context(context), gameObjectsUpdate(gameObjectsUpdate) {
		}

        ~Scene2D() {
            if (camera)
                camera->release();
            for (auto& entity : entities) {
                gameObjectsUpdate.remove(entity);
                gameObjectsDraw.remove(entity);
            }
        }

        inline Camera2D* getCamera() const {
            return camera;
        }

        inline void setCamera(Camera2D* camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera2D* Camera;

        inline void add(IntrusivePointer<Entity2D> entity) {
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
            return Scene2D::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}