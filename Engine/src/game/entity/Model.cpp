#include "Model.h"
#include "graphics/RenderStep.h"

namespace Ghurund {
    Status Model::loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) {
        Status result;
        mesh = (Ghurund::Mesh*)resourceManager.load(context, workingDir, stream, &result, options);
        if(filterStatus(result, options)!=Status::OK)
            return result;

        material = (Ghurund::Material*)resourceManager.load(context, workingDir, stream, &result, options);
        return filterStatus(result, options);
    }

    Status Model::saveInternal(ResourceManager &resourceManager, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const {
        if(mesh==nullptr) {
            Logger::log(_T("Mesh cannot be empty\n"));
            return Status::INV_STATE;
        }

        if(material==nullptr) {
            Logger::log(_T("Material cannot be empty\n"));
            return Status::INV_STATE;
        }

        Status result;
        result = resourceManager.save(*mesh, workingDir, stream, options);
        if(filterStatus(result, options)!=Status::OK)
            return result;
        result = resourceManager.save(*material, workingDir, stream, options);
        return filterStatus(result, options);
    }

    void Model::flatten(RenderStep &step, XMFLOAT4X4 &transformation) {
        step.addModel(ghnew GlobalEntity<Model>(*this, mesh->BoundingBox, transformation));
    }
}