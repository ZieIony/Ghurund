#include "Material.h"
#include "Graphics.h"
#include "resource/ResourceManager.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    Status Material::loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        Status result;
        shader = resourceManager.load<Ghurund::Shader>(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        return loadParameters(resourceManager, context, workingDir, stream, options);
    }

    Status Material::saveInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        if (shader == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Shader cannot be empty\n"));

        Status result = resourceManager.save(*shader, context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        return saveParameters(resourceManager, context, workingDir, stream, options);
    }
}