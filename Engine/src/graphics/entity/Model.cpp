#include "Model.h"
#include "graphics/RenderStep.h"

namespace Ghurund {
    Status Model::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        __super::loadInternal(context, workingDir, stream, options);

        Status result;
        mesh = (Ghurund::Mesh*)context.ResourceManager.load(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        material = (Ghurund::Material*)context.ResourceManager.load(context, workingDir, stream, &result, options);

        initParameters(context.ParameterManager);

        return filterStatus(result, options);
    }

    Status Model::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        if (mesh == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Mesh cannot be empty"));

        if (material == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Material cannot be empty"));

        __super::saveInternal(context, workingDir, stream, options);

        Status result;
        result = context.ResourceManager.save(*mesh, context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK)
            return result;
        result = context.ResourceManager.save(*material, context, workingDir, stream, options);
        return filterStatus(result, options);
    }

    void Model::queueDraw(RenderStep& step, XMFLOAT4X4& transformation) {
        if (!Visible)
            return;

        XMFLOAT4X4 localTransformation = getTransformation();
        XMFLOAT4X4 dest;
        XMStoreFloat4x4(&dest, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&localTransformation));
        step.addModel(ghnew GlobalEntity(*this, mesh->BoundingBox, dest));
    }
}