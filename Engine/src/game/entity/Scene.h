#pragma once

#include "game/entity/EntityGroup.h"
#include "physics/Physics.h"

#include <PxScene.h>
#include <extensions/PxDefaultCpuDispatcher.h>

using namespace physx;

namespace Ghurund {

    class Scene:public EntityGroup {
    private:
        Array<Parameter*> parameters;
        PxDefaultCpuDispatcher* dispatcher = nullptr;

    public:

        Scene():parameters(Array<Parameter*>(0)) {
            Name = _T("scene");
        }

        Scene(const std::initializer_list<Entity*> list):EntityGroup(list), parameters(Array<Parameter*>(0)) {
            Name = _T("scene");
        }

        PxScene* scene = nullptr;

        void init(Physics& physics) {
            PxSceneDesc sceneDesc(physics.get().getTolerancesScale());
            sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
            dispatcher = PxDefaultCpuDispatcherCreate(0);
            sceneDesc.cpuDispatcher = dispatcher;
            sceneDesc.filterShader = PxDefaultSimulationFilterShader;
            scene = physics.get().createScene(sceneDesc);
        }

        void simulate(float dt) {
            scene->simulate(dt);
            scene->fetchResults(true);
        }

        virtual Array<Parameter*>& getParameters() {
            return parameters;
        }

        virtual const Ghurund::Type& getType() const override {
            return Type::SCENE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::SCENE};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}