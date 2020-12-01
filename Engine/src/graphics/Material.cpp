#include "Material.h"
#include "Graphics.h"
#include "resource/ResourceManager.h"
#include "core/SharedPointer.h"

namespace Ghurund {
	Status Material::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        Status result;
        shader = context.ResourceManager.load<Ghurund::Shader>(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        initParameters(context.ParameterManager);

        return loadParameters(context, workingDir, stream, options);
    }

    Status Material::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        if (shader == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Shader cannot be empty\n"));

        Status result = context.ResourceManager.save(*shader, context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        return saveParameters(context, workingDir, stream, options);
    }
}