#pragma once

#include "Ghurund.h"
#include "resource/File.h"
#include "collection/Map.h"
#include "collection/String.h"

namespace Ghurund {
    class Settings {
    public:
        unsigned int width, height;

        bool windowed;

        Settings() {
            reset();
        }

        void reset() {
            width = 800;
            height = 600;
            windowed = true;
        }

        void parse(const String &settings) {
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

        Status load(const tchar *fileName) {
            File file(fileName);
            file.read();
            *this = *(Settings*)file.Data;
            return Status::OK;
        }

        Status save(const tchar *fileName)const {
            File file(fileName);
            file.setData(this, sizeof(Settings));
            file.write();
            return Status::OK;
        }
    };

}