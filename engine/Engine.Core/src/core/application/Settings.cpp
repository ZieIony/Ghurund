#include "ghcpch.h"
#include "Settings.h"

#include "core/string/TextConversionUtils.h"

namespace Ghurund::Core {
    void Settings::load(const FilePath& path) {
        File file(path);
        Buffer buffer;
        file.read(buffer);
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)buffer.Data, buffer.Size);
        tinyxml2::XMLElement* child = doc.FirstChildElement();
        while (child) {
            const char* name = child->Name();
            values.set(name, child->Value());
            child = child->NextSiblingElement();
        }
    }

    void Settings::save(const FilePath& path) const {
        File file(path);
        tinyxml2::XMLDocument doc;
        for (size_t i = 0; i < values.Size; i++) {
            auto element = doc.NewElement(values.getKey(i).Data);
            element->SetText(values.getValue(i).Data);
        }
        tinyxml2::XMLPrinter printer;
        doc.Print(&printer);
        Buffer buffer(printer.CStr(), printer.CStrSize());
        file.write(buffer);
    }

}