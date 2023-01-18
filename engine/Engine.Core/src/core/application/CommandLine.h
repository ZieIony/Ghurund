#pragma once

#include "Common.h"
#include "core/string/TextConversionUtils.h"
#include "core/string/String.h"
#include "core/collection/Map.h"

namespace Ghurund::Core {
    class CommandLine {
    private:
        Map<AString, AString> parameters;

    public:
        CommandLine(const AString& commandLine = GetCommandLineA()) {
            Array<AString> commands = commandLine.split(" ");
            for (size_t i = 0; i < commands.Size; i++) {
                Array<AString> keyVal = commands[i].split("=");
                if (keyVal.Size != 2)
                    continue;
                parameters.set(keyVal[0], keyVal[1]);
            }
        }

        inline Map<AString, AString>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getValues)) Map<AString, AString>& Parameters;

        inline AString get(const AString& name) const {
            return parameters[name];
        }

        inline void set(const AString& name, const AString& value) {
            parameters.set(name, value);
        }
    };
}