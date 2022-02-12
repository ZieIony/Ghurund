#pragma once

#include "game/entity/Entity.h"
#include "game/parameter/Parameter.h"
#include "game/parameter/ParameterProvider.h"
#include "core/collection/PointerArray.h"
#include "core/resource/ResourceFormat.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class Light: public Pointer, public ParameterProvider {
    private:
        PointerArray<Parameter*> parameters;

        static const Ghurund::Core::Type& GET_TYPE();

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
        Light():parameters(PointerArray<Parameter*>(0)) {}

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = { ResourceFormat(L"light", true, true) };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}
