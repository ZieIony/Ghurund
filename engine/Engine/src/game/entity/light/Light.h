#pragma once

#include "game/entity/Entity.h"

namespace Ghurund {
    class Light: public Pointer, public ParameterProvider {
    private:
        PointerArray<Parameter*> parameters;

        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<Light>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Light))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            //__super::loadInternal(context, workingDir, stream, options);

            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            //__super::saveInternal(context, workingDir, stream, options);

            return Status::NOT_IMPLEMENTED;
        }

    public:
        Light():parameters(PointerArray<Parameter*>(0)) {
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

		inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"light", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}
