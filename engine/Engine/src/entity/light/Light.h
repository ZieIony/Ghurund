#pragma once

#include "parameter/Parameter.h"
#include "parameter/ParameterProvider.h"
#include "core/collection/PointerArray.h"
#include "core/resource/ResourceFormat.h"

#include "entity/Entity.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class Light: public RefCountedObject, public ParameterProvider {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Light::GET_TYPE();
#pragma endregion

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            //__super::loadInternal(context, workingDir, stream, options);

            throw NotImplementedException();
        }

        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            //__super::saveInternal(context, workingDir, stream, options);

            throw NotImplementedException();
        }

    public:
        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = { ResourceFormat(L"light", true, true) };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}
