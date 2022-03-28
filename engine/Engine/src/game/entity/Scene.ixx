module;

#include "core/resource/Resource.h"
#include "game/entity/camera/Camera.h"
#include "graphics/DrawingSystem.h"

#include <entt.hpp>

export module Ghurund.Engine.Game.Entity.Scene;

import Ghurund.Engine.Physics.Physics;
import Ghurund.Engine.Physics.PhysicsSystem;

export namespace Ghurund {
    class Scene:public Resource {
    private:
        entt::registry entityRegistry;

        PointerList<Entity*> entities;
        DrawingSystem drawingSystem;

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

    public:

        Scene() {}

        /*inline void init(ResourceContext& context) {
            drawingSystem.init(context.Graphics);
            drawingSystem.initParameters(context.ParameterManager);
        }*/

        inline void setCamera(Camera* camera) {
            drawingSystem.Camera = camera;
        }

        inline Camera* getCamera() {
            return drawingSystem.Camera;
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera* Camera;

        inline PointerList<Entity*>& getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) PointerList<Entity*>& Entities;

        inline DrawingSystem& getGraphicsSystem() {
            return drawingSystem;
        }

        __declspec(property(get = getGraphicsSystem)) DrawingSystem& DrawingSystem;

        inline void render(CommandList& commandList) {
        }

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"scene", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}