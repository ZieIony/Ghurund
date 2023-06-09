#include "ghpch.h"

#include "ParameterProvider.h"

#include "TextureParameter.h"
#include "ValueParameter.h"
#include "core/SharedPointer.h"
#include "core/resource/ResourceManager.h"
#include "core/directx/texture/Texture.h"
#include "core/io/File.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
    Status ParameterProvider::loadParameters(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
      /*  size_t paramCount = stream.readUInt();
        for (size_t i = 0; i < paramCount; i++) {
            char* name = stream.readASCII();
            Parameter* p = getParameter(name);

            if (!p) {
                Logger::log(LogType::ERR0R, _T("parameter {} not found while loading\n"), name);
                return Status::UNKNOWN;
            }
            if (p->ValueType.Value == ParameterTypeEnum::TEXTURE) {
                if (stream.readBoolean()) {
                    Status result;
                    SharedPointer<Texture> resource = (Texture*)context.ResourceManager.load(context, workingDir, stream, &result, options);
                    if (filterStatus(result, options) != Status::OK)
                        return result;
                    ((TextureParameter*)p)->setValue(resource);
                }
            } else {
                const void* bytes = stream.readBytes(p->ValueType.Size);
                ((ValueParameter*)p)->setValue(bytes);
            }
        }

        return Status::OK;*/
        return Status::NOT_IMPLEMENTED;
    }

    Status ParameterProvider::saveParameters(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
       /* List<Parameter*> paramsToSave;
        for (Parameter* p : Parameters) {
            if (p->Empty)
                continue;
            paramsToSave.add(p);
        }
        stream.writeUInt((unsigned int)paramsToSave.Size);
        for (Parameter* p : paramsToSave) {
            stream.writeASCII(p->ConstantName.Data);
            if (p->ValueType.Value == ParameterTypeEnum::TEXTURE) {
                Texture* texture = ((TextureParameter*)p)->Value;
                stream.writeBoolean(texture != nullptr);
                if (texture) {
                    Status result = context.ResourceManager.save(*texture, context, workingDir, stream, options);
                    if (filterStatus(result, options) != Status::OK)
                        return result;
                }
            } else {
                stream.writeBytes(((ValueParameter*)p)->Value, ((ValueParameter*)p)->ValueType.Size);
            }
        }

        return Status::OK;*/
        return Status::NOT_IMPLEMENTED;
    }
}