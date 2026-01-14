#pragma once

#include "core/resource/Resource.h"
#include "engine/graphics/DrawingSystem.h"
#include "engine/entity/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/physics/Physics.h"
#include "engine/physics/PhysicsSystem.h"

#include <entt.hpp>

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
        entt::registry entityRegistry;

        List<IntrusivePointer<Entity>> entities;
        DrawingSystem drawingSystem;

    public:
        Scene() {}

        /*inline void init(ParameterManager& parameterManager) {
            drawingSystem.initParameters(parameterManager);
        }*/

        virtual void invalidate() override {
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return __super::isValid();
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