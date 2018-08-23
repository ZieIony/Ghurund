#include "Model.h"
#include "RenderingBatch.h"

namespace Ghurund {
    Status Model::loadInternal(ResourceManager & resourceManager, MemoryInputStream &stream, LoadOption options) {
        Status result;
        mesh = (Ghurund::Mesh*)resourceManager.load(stream, &result, options);
        if(result!=Status::OK)
            return result;

        material = (Ghurund::Material*)resourceManager.load(stream, &result, options);
        return result;
    }

    Status Model::saveInternal(ResourceManager & resourceManager, MemoryOutputStream &stream, SaveOption options) const {
        if(mesh==nullptr) {
            Logger::log(_T("Mesh cannot be empty\n"));
            return Status::INV_STATE;
        }

        if(material==nullptr) {
            Logger::log(_T("Material cannot be empty\n"));
            return Status::INV_STATE;
        }

        resourceManager.save(*mesh, stream, options);
        resourceManager.save(*material, stream, options);

        return Status::OK;
    }

    void Model::flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) {
        batch.addModel(new GlobalEntity<Model>(*this, transformation));
    }
}