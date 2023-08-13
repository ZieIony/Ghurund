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
        Settings() {}

        Settings(const Map<AString, AString>& values) :values(values) {}

        Settings(const Settings& other) :values(other.values) {}

        Settings(Settings&& other) noexcept :values(std::move(other.values)) {}

        Settings& operator=(const Settings& other) {
            if (this == &other)
                return *this;
            values = other.values;
            return *this;
        }

        Settings& operator=(Settings&& other) noexcept {
            if (this == &other)
                return *this;
            values = std::move(other.values);
            return *this;
        }

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

        void load(const FilePath& path);

        void save(const FilePath& path) const;
    };

}