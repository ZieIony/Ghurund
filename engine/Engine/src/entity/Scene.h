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

        List<IntrusivePointer<Entity>> entities;
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

        inline List<IntrusivePointer<Entity>>& getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) List<IntrusivePointer<Entity>>& Entities;

        inline DrawingSystem& getGraphicsSystem() {
            return drawingSystem;
        }

        __declspec(property(get = getGraphicsSystem)) DrawingSystem& DrawingSystem;

        inline void render(CommandList& commandList) {
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", true, true);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}