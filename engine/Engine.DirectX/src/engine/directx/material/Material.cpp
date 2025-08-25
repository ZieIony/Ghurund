#include "ghedxpch.h"

#include "Material.h"

#include "engine/directx/DxGraphics.h"
#include "core/resource/ResourceManager.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Material>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Material::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        /*Status result;
        shader = context.ResourceManager.load<Ghurund::Shader>(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        initParameters(context.ParameterManager);

        return loadParameters(context, workingDir, stream, options);*/
        throw NotImplementedException();
    }

    void Material::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        /*if (shader == nullptr)
            return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Shader cannot be empty\n"));

        Status result = context.ResourceManager.save(*shader, context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK)
            return result;

        return saveParameters(context, workingDir, stream, options);*/
        throw NotImplementedException();
    }
}