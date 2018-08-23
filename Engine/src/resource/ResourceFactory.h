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
    public:
        virtual Resource *makeResource(MemoryInputStream &stream) override {
            unsigned int index = stream.read<unsigned int>();
            const Type *type = Type::getValues()[index];

            return (Resource*)type->newInstance();
        }

        virtual void describeResource(const Resource &resource, MemoryOutputStream &stream) override {
            stream.write(resource.getType().Value);
        }

    };
}