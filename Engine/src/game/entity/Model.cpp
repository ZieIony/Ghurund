#include "Model.h"
#include "graphics/RenderingBatch.h"

namespace Ghurund {
    Status Model::loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
        Status result;
        mesh = (Ghurund::Mesh*)resourceManager.load(context, stream, &result, options);
        if(filterStatus(result, options)!=Status::OK)
            return result;

        material = (Ghurund::Material*)resourceManager.load(context, stream, &result, options);
        return filterStatus(result, options);
    }

    Status Model::saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
        if(mesh==nullptr) {
            Logger::log(_T("Mesh cannot be empty\n"));
            return Status::INV_STATE;
        }

        if(material==nullptr) {
            Logger::log(_T("Material cannot be empty\n"));
            return Status::INV_STATE;
        }

        Status result;
        result = resourceManager.save(*mesh, stream, options);
        if(filterStatus(result, options)!=Status::OK)
            return result;
        result = resourceManager.save(*material, stream, options);
        return filterStatus(result, options);
    }

    void Model::flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) {
        batch.addModel(new GlobalEntity<Model>(*this, mesh->BoundingBox, transformation));
    }
}