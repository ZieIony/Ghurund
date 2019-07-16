#pragma once

#include "Resource.h"

namespace Ghurund {
    class ResourceFactory {
    public:
        virtual ~ResourceFactory() {}

        /*
        Reads resource description from the stream and returns a new instance of correct resource class
        */
        virtual Resource *makeResource(MemoryInputStream &stream) = 0;

        /*
        Writes resource description to the stream
        */
        virtual void describeResource(const Resource &resource, MemoryOutputStream &stream) = 0;
    };

    class DefaultResourceFactory: public ResourceFactory {
    private:
        List<Type*> types;

    public:
		DefaultResourceFactory();

        void addType(const Type &type) {
            types.add((Type*)&type);
        }

        virtual Resource *makeResource(MemoryInputStream &stream) override {
            size_t index = stream.readUInt();
            const Type *type = types[index];

            return (Resource*)type->newInstance();
        }

        virtual void describeResource(const Resource &resource, MemoryOutputStream &stream) override {
            size_t index = types.indexOf((Type*)&resource.getType());
            stream.writeUInt((uint32_t)index);
        }
    };
}
