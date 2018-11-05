#pragma once

#include "game/Entity.h"

namespace Ghurund {
    class Light: public Entity {
    private:
        XMFLOAT3 target;
        Array<Parameter*> parameters;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
            return Status::NOT_IMPLEMENTED;
        }

    public:
        Light():parameters(Array<Parameter*>(0)) {
            Name = _T("light");
        }

        virtual Array<Parameter*> &getParameters() override {
            return parameters;
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::LIGHT;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override;
    };
}