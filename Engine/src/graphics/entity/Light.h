#pragma once

#include "Target.h"
#include "ecs/Entity.h"

namespace Ghurund {
    class Light: public Entity, public ParameterProvider {
    private:
        Target* target;
        PointerArray<Parameter*> parameters;

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            __super::loadInternal(context, workingDir, stream, options);

            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            __super::saveInternal(context, workingDir, stream, options);

            return Status::NOT_IMPLEMENTED;
        }

    public:
        Light():parameters(PointerArray<Parameter*>(0)) {
            Name = _T("light");
        }

        inline void setTarget(Target* target) {
            this->target = target;
        }

        inline const Target* getTarget() const {
            return target;
        }

        __declspec(property(get = getTarget, put = setTarget)) Target* Target;

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        virtual const Ghurund::Type& getType() const override {
            return Type::LIGHT;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::ENTITY};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}