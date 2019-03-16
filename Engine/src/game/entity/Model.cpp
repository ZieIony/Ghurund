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
        if(mesh==nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Mesh cannot be empty"));

        if(material==nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Material cannot be empty"));

        Status result;
        result = resourceManager.save(*mesh, workingDir, stream, options);
        if(filterStatus(result, options)!=Status::OK)
            return result;
        result = resourceManager.save(*material, workingDir, stream, options);
        return filterStatus(result, options);
    }

    void Model::flatten(RenderStep &step, XMFLOAT4X4 &transformation) {
        XMFLOAT4X4 localTransformation = getTransformation();
        XMFLOAT4X4 dest;
        XMStoreFloat4x4(&dest, XMLoadFloat4x4(&transformation)*XMLoadFloat4x4(&localTransformation));
        step.addModel(ghnew GlobalEntity<Model>(*this, mesh->BoundingBox, dest));
    }
}