#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
    template<typename CharT>
    class NamedObject {
    private:
        GenericString<CharT> name;

    public:
        NamedObject() {}

        NamedObject(const GenericString<CharT>& name):name(name) {}

        virtual ~NamedObject() = 0 {};

        virtual void setName(const GenericString<CharT>& name) {
            this->name = name;
        }

        virtual const GenericString<CharT>& getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) const GenericString<CharT>& Name;

        bool operator==(const NamedObject<CharT>& other) const {
            return Name == other.Name == 0;
        }
    };
}