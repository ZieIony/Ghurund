#pragma once

#include "Resource.h"
#include "collection/String.h"

namespace Ghurund {
    class DataResource:public Resource {
    private:
        void *data = nullptr;
        size_t size;

    protected:
        Status loadInternal(shared_ptr<ResourceManager>, const void *data, unsigned long size, unsigned int flags = 0) {
            if(this->data!=nullptr)
                delete this->data;
            this->data = ghnew char[size];
            memcpy(this->data, data, size);
            this->size = size;

            return Status::OK;
        }

        virtual Status saveInternal(shared_ptr<ResourceManager>, void **data, unsigned long *size, unsigned int flags = 0)const {
            *data = ghnew char[this->size];
            memcpy(*data, this->data, this->size);
            *size = this->size;

            return Status::OK;
        }

    public:
        ~DataResource() {
            delete[] data;
        }

        void *getData() {
            return data;
        }

        void setData(const void *data, size_t size) {
            delete[] this->data;
            this->data = ghnew BYTE[size];
            memcpy(this->data, data, size);
            this->size = size;
        }

        size_t getSize() {
            return size;
        }
    };
}