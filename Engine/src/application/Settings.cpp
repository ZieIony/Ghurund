#include "Settings.h"

namespace Ghurund {
    void Settings::parse(const String & settings) {
        List<String> commands = settings.split(" ");
        for(size_t i = 0; i<commands.Size; i++) {
            List<String> keyVal = commands[i].split("=");
            if(keyVal.Size!=2)
                return;
            if(keyVal[0]=="width")
                width = _ttoi(keyVal[1].getData());
            if(keyVal[0]=="height")
                height = _ttoi(keyVal[1].getData());
            if(keyVal[0]=="windowed")
                windowed = keyVal[1]=="true";
        }
    }
}