#include "ParameterProvider.h"
#include "ResourceParameter.h"
#include "core/ScopedPointer.h"
#include "resource/ResourceContext.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    Status ParameterProvider::loadParameters(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        size_t paramCount = stream.readUInt();
        for (size_t i = 0; i < paramCount; i++) {
            char* name = stream.readASCII();
            Parameter* p = getParameter(name);

            if (!p) {
                Logger::log(LogType::ERR0R, _T("parameter %hs not found while loading material\n"), name);
                return Status::UNKNOWN;
            }
            if (p->ValueType.Value == ParameterTypeEnum::TEXTURE) {
                Status result;
                ScopedPointer<Resource> resource = resourceManager.load(context, workingDir, stream, &result, options);
                if (filterStatus(result, options) != Status::OK)
                    return result;
                ((ResourceParameter*)p)->setValue(resource);
            } else {
                const void* bytes = stream.readBytes(p->ValueType.Size);
                ((ValueParameter*)p)->setValue(bytes);
            }
        }

        return Status::OK;
    }

    Status ParameterProvider::saveParameters(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        List<Parameter*> paramsToSave;
        for (Parameter* p : Parameters) {
            if (!p)
                continue;
            for (Parameter* mp : context.ParameterManager.Parameters) {
                if (mp->Name == p->Name)
                    continue;
            }
            paramsToSave.add(p);
        }
        stream.writeUInt(paramsToSave.Size);
        for (Parameter* p : paramsToSave) {
            stream.writeASCII(p->Name);
            if (p->ValueType.Value == ParameterTypeEnum::TEXTURE) {
                Status result = resourceManager.save(*((ResourceParameter*)p)->Value, context, workingDir, stream, options);
                if (filterStatus(result, options) != Status::OK)
                    return result;
            } else {
                stream.writeBytes(((ValueParameter*)p)->Value, ((ValueParameter*)p)->ValueType.Size);
            }
        }

        return Status::OK;
    }
}