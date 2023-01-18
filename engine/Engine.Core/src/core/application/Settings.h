#pragma once

#include "Common.h"
#include "core/collection/Map.h"
#include "core/io/File.h"
#include "core/string/String.h"

#include <tinyxml2.h>

namespace Ghurund::Core {
    class Settings {
    private:
        Map<AString, AString> values;

    public:
        inline Map<AString, AString>& getValues() {
            return values;
        }

        __declspec(property(get = getValues)) Map<AString, AString>& Values;

        inline AString get(const AString& name) const {
            return values[name];
        }

        inline void set(const AString& name, const AString& value) {
            values.set(name, value);
        }

        Status load(const FilePath& path);

        Status save(const FilePath& path) const;
    };

}