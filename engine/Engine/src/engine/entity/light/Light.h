#pragma once

#include "engine/parameter/ParameterProvider.h"

namespace Ghurund::Engine {
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
    };
}
