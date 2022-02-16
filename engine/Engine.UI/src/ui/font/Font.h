#pragma once

#include "core/resource/Resource.h"
#include "core/reflection/Type.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Font:public Ghurund::Core::Resource {
#pragma region reflection
    public:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override { return GET_TYPE(); }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
#pragma endregion

    protected:
        Ghurund::Core::WString familyName;

    public:
        const Ghurund::Core::WString& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::WString& FamilyName;

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = {};

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}