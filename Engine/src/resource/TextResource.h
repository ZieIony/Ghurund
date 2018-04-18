#pragma once

#include "Resource.h"
#include "collection/String.h"

namespace Ghurund {
    class TextResource:public Resource {
    private:
        String *text = nullptr;

    protected:
        virtual unsigned int getVersion()const {
            return 0;
        }

        Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) {
            if(text!=nullptr)
                delete text;
            text = ghnew String((tchar*)data, size);

            return Status::OK;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            *size = text->Size*sizeof(tchar);
            *data = ghnew char[*size];
            memcpy(*data, text->getData(), *size);

            return Status::OK;
        }

        virtual void clean() {
            delete text;
            text = nullptr;
        }

    public:
        ~TextResource() {
            clean();
        }

        String &getText() {
            return *text;
        }
    };
}