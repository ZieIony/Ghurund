#pragma once

#include "Common.h"
#include "core/collection/Map.h"
#include "core/io/File.h"
#include "core/math/Size.h"
#include "core/string/String.h"
#include "core/DataParsing.h"

#include <tinyxml2.h>

namespace Ghurund::Core {
    enum class SettingType {
        BOOL, INT, FLOAT, STRING, ENUM
    };

    struct AllowedSetting {
        SettingType type;
        AString defaultValue;
        List<AString> options;
    };

    class Settings {
    private:
        Map<AString, AString> values;
        Map<AString, AllowedSetting> allowed = {
            {
                "width", { SettingType::INT, "800" }
            },
            {
                "height", { SettingType::INT, "600" }
            },
            {
                "windowed", { SettingType::BOOL, "true" }
            },
            {   // name of the selected graphics adapter, empty if any is allowed
                "graphics", SettingType::STRING
            }
        };

    public:
        Settings() {
            reset();
        }

        inline Map<AString, AString>& getValues() {
            return values;
        }

        __declspec(property(get = getValues)) Map<AString, AString>& Values;

        inline Map<AString, AllowedSetting>& getAllowed() {
            return allowed;
        }

        __declspec(property(get = getAllowed)) Map<AString, AllowedSetting>& Allowed;

        template<typename Result>
        inline Result get(const AString& name) const {
            return Ghurund::Core::parse<Result>(values[name]);
        }

        void reset() {
            for (auto& [name, setting] : allowed)
                values.set(name, setting.defaultValue);
        }

        void parse(const String& settings);

        Status load(const FilePath& path) {
            File file(path);
            file.read();
            tinyxml2::XMLDocument doc;
            doc.Parse((const char*)file.Data, file.Size);
            tinyxml2::XMLElement* child = doc.FirstChildElement();
            while (child) {
                const char* name = child->Name();
                if (Allowed.containsKey(name))
                    Values.set(name, child->Value());
                child = child->NextSiblingElement();
            }
            return Status::OK;
        }

        Status save(const FilePath& path)const {
            File file(path);
            tinyxml2::XMLDocument doc;
            for (size_t i = 0; i < values.Size; i++) {
                auto element = doc.NewElement(values.getKey(i).Data);
                element->SetText(values.getValue(i).Data);
            }
            tinyxml2::XMLPrinter printer;
            doc.Print(&printer);
            file.setData(printer.CStr(), printer.CStrSize());
            file.write();
            return Status::OK;
        }
    };

}