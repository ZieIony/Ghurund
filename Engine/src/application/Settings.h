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

        void parse(const String &settings);

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