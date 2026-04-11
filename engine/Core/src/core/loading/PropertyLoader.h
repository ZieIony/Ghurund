#pragma once

#include "core/io/DirectoryPath.h"
#include "core/object/Object.h"
#include "core/reflection/BaseProperty.h"
#include "core/xml/XMLElement.h"

#include <exception>

namespace Ghurund::Core {
    class PropertyTypeNotSupportedException:public std::exception {};

    class PropertyLoader {
    public:
        virtual ~PropertyLoader() {}

        virtual const Type& getType() const = 0;

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
            throw PropertyTypeNotSupportedException();
        }

        virtual void loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const XMLElement& xml) const {
            throw PropertyTypeNotSupportedException();
        }

        virtual void loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const XMLElement& xml) const {
            throw PropertyTypeNotSupportedException();
        }
    };
}