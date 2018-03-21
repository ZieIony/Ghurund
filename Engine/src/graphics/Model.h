#pragma once

#include "Mesh.h"
#include "Material.h"
#include "graphics/mesh/TriangleMesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class Model {
    private:
        Mesh *mesh;
        Material *material;

    public:
        ~Model() {
            delete mesh;
            delete material;
        }

        Status init(ResourceManager &resourceManager) {
            material = ghnew Material();
            Status result = material->load(resourceManager, &String(_T("material.mtr")));
            if(result!=Status::OK)
                return result;

            mesh = ghnew TriangleMesh();
            mesh->load(resourceManager, nullptr, 0, 0);

            return Status::OK;
        }

        void draw(ID3D12GraphicsCommandList *commandList) {
            material->set(commandList);
            mesh->draw(commandList);
        }
    };
}