#include "Material.h"
#include "Graphics.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    Status Material::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags) {
        MemoryInputStream stream = MemoryInputStream(data);

        Status result = shader.load(resourceManager, &String(stream.readString()));

        image.loadImageDataFromFile(resourceManager, _T("cow.jpg"));
        texture.init(resourceManager.getGraphics(), resourceManager.getCommandList()->get(), &image);

        return result;
    }

    Status Material::saveInternal(ResourceManager & resourceManager, void ** data, unsigned long * size, unsigned int flags) const {
        MemoryOutputStream stream = MemoryOutputStream(data);

        stream.writeString(shader.FileName.getData());

        *size = stream.getBytesWritten();

        return Status::OK;
    }
}