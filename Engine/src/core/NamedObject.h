#pragma once

namespace Ghurund {
    template <class T> class NamedObject {
    private:
        T name;

    public:
        virtual ~NamedObject() = default;

        virtual void setName(const T &name) {
            this->name = name;
        }
        
        virtual const T &getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) T &Name;
    };
}