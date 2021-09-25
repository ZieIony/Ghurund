#include "ghpch.h"
#include "Material.h"

#include "Graphics.h"
#include "core/resource/ResourceManager.h"
#include "core/SharedPointer.h"

namespace Ghurund {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Material>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Material>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Material))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status Material::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        /*Status result;
        shader = context.ResourceManager.load<Ghurund::Shader>(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        initParameters(context.ParameterManager);

        return loadParameters(context, workingDir, stream, options);*/
        return Status::NOT_IMPLEMENTED;
    }

    Status Material::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        /*if (shader == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Shader cannot be empty\n"));

        Status result = context.ResourceManager.save(*shader, context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        return saveParameters(context, workingDir, stream, options);*/
        return Status::NOT_IMPLEMENTED;
    }
}