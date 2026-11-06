#pragma once

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "core/resource/ResourceManager.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/material/Material.h"
#include <engine/ecs/SceneLoader.h>

namespace Ghurund::Engine::_3D {
    using namespace Ghurund::Core;

    class Graphics3DFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Graphics3DFeature::GET_TYPE();
#pragma endregion

    private:
        void uninitGraphicsFeature();

    protected:
        ResourceManager& resourceManager;
        SceneLoader& sceneLoader;

        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onDeinit() override;

    public:
        inline static Mesh* MESH_CUBE = nullptr;

        inline static Material* MATERIAL_FORWARD_BASIC = nullptr;
        inline static Material* MATERIAL_FORWARD_LIT = nullptr;
        inline static Material* MATERIAL_FORWARD_NORMALS = nullptr;
        inline static Material* MATERIAL_FORWARD_TANGENTS = nullptr;
        inline static Material* MATERIAL_FORWARD_TEXCOORDS = nullptr;

        Graphics3DFeature(
            ResourceManager& resourceManager,
            SceneLoader& sceneLoader
        ):resourceManager(resourceManager), sceneLoader(sceneLoader) {}

        virtual ~Graphics3DFeature() = 0 {
            if (IsInitialized)
                uninitGraphicsFeature();
        }
    };
}
