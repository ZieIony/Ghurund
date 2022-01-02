#include "ghcpch.h"
#include "Settings.h"

#include "core/string/TextConversionUtils.h"

namespace Ghurund::Core {
    void Settings::parse(const String& settings) {
        AString aSettings = convertText<tchar, char>(settings);
        Array<AString> commands = aSettings.split(" ");
        for (size_t i = 0; i < commands.Size; i++) {
            Array<AString> keyVal = commands[i].split("=");
            if (keyVal.Size != 2)
                continue;
            if (allowed.containsKey(keyVal[0]))
                values.set(keyVal[0], keyVal[1]);
        }
    }
}