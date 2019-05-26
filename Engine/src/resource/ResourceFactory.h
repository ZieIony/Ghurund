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
        DefaultResourceFactory() {
            addType(Type::CAMERA);
            addType(Type::LIGHT);
            addType(Type::MESH);
            addType(Type::MODEL);
            addType(Type::TEXTURE);
            addType(Type::MATERIAL);
            addType(Type::IMAGE);
            addType(Type::SHADER);
            addType(Type::SCENE);
        }

        void addType(const Type &type) {
            types.add((Type*)&type);
        }

        virtual Resource *makeResource(MemoryInputStream &stream) override {
            unsigned int index = stream.read<unsigned int>();
            const Type *type = types[index];

            return (Resource*)type->newInstance();
        }

        virtual void describeResource(const Resource &resource, MemoryOutputStream &stream) override {
            size_t index = types.indexOf((Type*)&resource.getType());
            stream.write(index);
        }
    };
}
