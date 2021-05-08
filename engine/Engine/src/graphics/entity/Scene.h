#pragma once

#include "ecs/Entity.h"
#include "core/resource/Resource.h"
#include "physics/Physics.h"
#include "physics/PhysicsSystem.h"
#include "graphics/DrawingSystem.h"

namespace Ghurund {
    class Scene:public Resource {
    private:
        PointerList<Entity*> entities;
        TransformSystem transformSystem;
        Physics::PhysicsSystem physicsSystem;
        DrawingSystem drawingSystem;

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

        static const Ghurund::Type& GET_TYPE();

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

        inline TransformSystem& getTransformSystem() {
            return transformSystem;
        }

        __declspec(property(get = getTransformSystem)) TransformSystem& TransformSystem;

        inline DrawingSystem& getGraphicsSystem() {
            return drawingSystem;
        }

        __declspec(property(get = getGraphicsSystem)) DrawingSystem& DrawingSystem;

        inline void transform() {
            transformSystem.update(0);
        }

        inline void render(CommandList& commandList) {
            drawingSystem.draw(commandList, transformSystem);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"scene", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}