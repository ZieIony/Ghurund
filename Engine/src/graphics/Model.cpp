#include "Model.h"

namespace Ghurund {
    Status Model::loadInternal(ResourceManager & resourceManager, const void * data, unsigned long size, unsigned long *bytesRead) {
        MemoryInputStream stream = MemoryInputStream(data);

        mesh.reset(ghnew Ghurund::Mesh());
        Status result = mesh->load(resourceManager, stream.readString());
        if(result!=Status::OK)
            return result;

        material.reset(ghnew Ghurund::Material());
        material->load(resourceManager, stream.readString());
        if(result!=Status::OK)
            return result;

        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;

        return Status::OK;
    }

    Status Model::saveInternal(ResourceManager & resourceManager, void ** data, unsigned long * size) const {
        MemoryOutputStream stream = MemoryOutputStream(data);

        if(mesh==nullptr) {
            Logger::log(_T("Mesh cannot be empty\n"));
            return Status::INV_STATE;
        }

        if(material==nullptr) {
            Logger::log(_T("Material cannot be empty\n"));
            return Status::INV_STATE;
        }

        stream.writeString(mesh->FileName);
        stream.writeString(material->FileName);

        *size = stream.getBytesWritten();

        return Status::OK;
    }
}