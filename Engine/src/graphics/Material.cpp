#include "Material.h"
#include "Graphics.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    const List<ResourceFormat> Material::formats = {ResourceFormat::AUTO, ResourceFormat::MATERIAL};

    Status Material::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
        MemoryInputStream stream = MemoryInputStream(data);

        shader.reset(ghnew Ghurund::Shader());
        Status result = shader->load(resourceManager, stream.readString());
        if(result!=Status::OK)
            return result;

		texture.reset(ghnew Ghurund::Texture());
        return texture->load(resourceManager, stream.readString());
    }

    Status Material::saveInternal(ResourceManager & resourceManager, void ** data, unsigned long * size) const {
        MemoryOutputStream stream = MemoryOutputStream(data);

        if(shader==nullptr) {
            Logger::log(_T("Shader cannot be empty\n"));
            return Status::INV_STATE;
        }

        stream.writeString(shader->FileName);
        stream.writeString(texture->FileName);

        *size = stream.getBytesWritten();

        return Status::OK;
    }
}