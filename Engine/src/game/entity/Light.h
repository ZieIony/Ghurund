#pragma once

#include "Target.h"
#include "game/entity/Entity.h"

namespace Ghurund {
    class Light: public TranslatedEntity {
    private:
        Target* target;
        Array<Parameter*> parameters;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) {
            __super::loadInternal(resourceManager, context, workingDir, stream, options);
   
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const {
            __super::saveInternal(resourceManager, context, workingDir, stream, options);
  
            return Status::NOT_IMPLEMENTED;
        }

    public:
        Light():parameters(Array<Parameter*>(0)) {
            Name = _T("light");
        }

        inline void setTarget(Target* target) {
            this->target = target;
        }

        inline const Target *getTarget() const {
            return target;
        }

        __declspec(property(get = getTarget, put = setTarget)) Target *Target;

        virtual Array<Parameter*> &getParameters() override {
            return parameters;
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::LIGHT;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::ENTITY};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;

        virtual void flatten(RenderStep &step, XMFLOAT4X4 &transformation) override;
    };
}