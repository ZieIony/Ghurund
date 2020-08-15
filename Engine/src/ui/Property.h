#pragma once

namespace Ghurund::UI {
    template<class Type>
    class Property {
    private:
        Type value;
        List<std::function<void(SenderType& sender, const Type& args)>> listeners;

    public:
        Property(const Type& v) {
            this->value = v;
        }

        operator Type&() const {
            return value;
        }

        inline Property<Type>& operator=(const Type& v) {
            this->value = v;
            return *this;
        }

        inline bool operator==(const Property& p) const {
            return this->value == p.value;
        }

        inline bool operator==(const Property& p) {
            return this->value == p.value;
        }

        void add(std::function<void(SenderType& sender, const Type& args)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }
    };
}