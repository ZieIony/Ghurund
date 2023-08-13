#pragma once

#include "core/Object.h"
#include "core/reflection/BaseProperty.h"

#include <exception>
#include <tinyxml2.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class PropertyTypeNotSupportedException:public std::exception {};

    class PropertyLoader {
    public:
        virtual ~PropertyLoader() {}

        virtual const Type& getType() const = 0;

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
            throw PropertyTypeNotSupportedException();
        }

        virtual void loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
            throw PropertyTypeNotSupportedException();
        }

        virtual void loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
            throw PropertyTypeNotSupportedException();
        }
    };
}