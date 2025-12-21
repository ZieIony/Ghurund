#pragma once

#include "core/resource/Resource.h"
#include "engine/parameter/ParameterCollection.h"

namespace Ghurund::Engine {

    class IMaterial:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = IMaterial::GET_TYPE();
#pragma endregion

    protected:
        IMaterial() {}

        IMaterial(const IMaterial& other):Resource(other) {}

    public:
        ~IMaterial() = 0 {}

        virtual bool getIsTransparencyEnabled() const = 0;

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        virtual const ParameterCollection& getParameters() const = 0;

        __declspec(property(get = getParameters)) const ParameterCollection& Parameters;
    };
}