#include "Settings.h"

namespace Ghurund {
    void Settings::parse(const String& settings) {
        Array<String> commands = settings.split(_T(" "));
        for (size_t i = 0; i < commands.Size; i++) {
            Array<String> keyVal = commands[i].split(_T("="));
            if (keyVal.Size != 2)
                return;
            if (keyVal[0] == "width")
                width = _ttoi(keyVal[1].getData());
            if (keyVal[0] == "height")
                height = _ttoi(keyVal[1].getData());
            if (keyVal[0] == "windowed")
                windowed = keyVal[1] == "true";
        }
    }
}