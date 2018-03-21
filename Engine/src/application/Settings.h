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

        void parse(const tchar *settings) {
            tchar *copy = ghnew tchar[_tcslen(settings)+1];
            _tcscpy_s(copy, _tcslen(settings)+1, settings);
            tchar *nextToken;
            tchar *key = _tcstok_s(copy, _T("="), &nextToken);
            tchar *value;

            Map<String, tchar*> map;

            while(key != nullptr) {
                value = _tcstok_s(nullptr, _T(" "), &nextToken);
                map.set(String(key), value);
                key = _tcstok_s(nullptr, _T("="), &nextToken);
            }

            String widthKey(_T("width"));
            if(map.contains(widthKey))
                width = _ttoi(map.get(widthKey));

            String heightKey(_T("height"));
            if(map.contains(heightKey))
                height = _ttoi(map.get(heightKey));

            String windowedKey(_T("windowed"));
            if(map.contains(windowedKey))
                windowed = map.get(windowedKey);

            delete[] copy;
        }

        void parse(String &settings) {
            parse(settings.getData());
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