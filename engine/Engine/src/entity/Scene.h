#pragma once

#include "core/resource/Resource.h"
#include "graphics/DrawingSystem.h"

#include <entt.hpp>

#include "entity/camera/Camera.h"
#include "entity/Entity.h"
#include "physics/Physics.h"
#include "physics/PhysicsSystem.h"

namespace Ghurund {
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
        entt::registry entityRegistry;

        PointerList<Entity*> entities;
        DrawingSystem drawingSystem;

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

    public:

        Scene() {}

        inline void init(Graphics& graphics, ParameterManager& parameterManager) {
            drawingSystem.init(graphics);
            drawingSystem.initParameters(parameterManager);
        }

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

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"scene", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}