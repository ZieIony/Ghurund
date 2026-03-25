#pragma once

#include "XMLElement.h"

#include "core/object/SharedPointer.h"
#include "core/string/String.h"

#include <xmllite.h>
#include <cstdint>

namespace Ghurund::Core {
    class XMLDocument {
    private:
        IXmlReader* reader;
        SharedPointer<XMLElement> root;

        inline WString readName() {
            const wchar_t* name;
            uint32_t nameSize;
            reader->GetLocalName(&name, &nameSize);
            return WString(name, nameSize);
        }

        inline WString readValue() {
            const wchar_t* value;
            uint32_t nameSize;
            reader->GetValue(&value, &nameSize);
            return WString(value, nameSize);
        }

    public:
		void parse(const void* data, uint32_t size);

        inline const XMLElement& getRoot() const {
            return root.ref();
        }

        __declspec(property(get = getRoot)) const XMLElement& Root;
    };
}
