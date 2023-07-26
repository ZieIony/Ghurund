#pragma once

namespace Ghurund::UI {
    template<typename Type>
    class AttributeKey {
    private:
        Ghurund::Core::AString str;

    public:
        AttributeKey(const Ghurund::Core::AString& str):str(str) {}

        const Ghurund::Core::AString& getValue() const {
            return str;
        }

        __declspec(property(get = getValue)) const Ghurund::Core::AString& Value;

        bool operator==(const AttributeKey& other) const {
            return str == other.str;
        }
    };
}