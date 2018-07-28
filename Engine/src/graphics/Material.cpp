#include "Material.h"
#include "Graphics.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    Status Material::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead) {
        MemoryInputStream stream = MemoryInputStream(data);

        shader.reset(ghnew Ghurund::Shader());
        Status result = shader->load(resourceManager, stream.readString());
        if(result!=Status::OK)
            return result;

        size_t textureCount = stream.read<size_t>();
        for(size_t i = 0; i<textureCount; i++) {
            ASCIIString name = stream.readASCII();
            shared_ptr<Texture> texture(ghnew Ghurund::Texture());
            result = texture->load(resourceManager, stream.readString());
            if(result!=Status::OK)
                return result;
            textures.set(name, texture);
        }

        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;

        return result;
    }

    Status Material::saveInternal(ResourceManager & resourceManager, void ** data, unsigned long * size) const {
        MemoryOutputStream stream = MemoryOutputStream(data);

        if(shader==nullptr) {
            Logger::log(_T("Shader cannot be empty\n"));
            return Status::INV_STATE;
        }

        stream.writeString(shader->FileName);
        stream.write(textures.Size);
        for(size_t i = 0; i<textures.Size; i++) {
            stream.writeASCII(textures.getKey(i));
            stream.writeString(textures.getValue(i)->FileName);
        }

        *size = stream.getBytesWritten();

        return Status::OK;
    }
}