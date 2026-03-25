#include "ghcpch.h"
#include "Settings.h"

#include "core/io/File.h"
#include "core/xml/XMLDocument.h"

namespace Ghurund::Core {
    void Settings::load(const void* data, uint32_t size) {
        XMLDocument doc;
        doc.parse(data, size);
        const XMLElement& root = doc.Root;
        for (auto& child : root.children) {
            WString name = child->attributes[L"name"];
            WString value = child->attributes[L"value"];
            values.put(name, value);
        }
    }

    void Settings::load(const FilePath& path) {
        File file(path);
        Buffer buffer;
        file.read(buffer);

        load(buffer.Data, buffer.Size);
    }

    void Settings::save(const FilePath& path) const {
        /*File file(path);
        tinyxml2::XMLDocument doc;
        for (auto& [key, value]:values) {
            auto element = doc.NewElement(key.Data);
            element->SetText(value.Data);
        }
        tinyxml2::XMLPrinter printer;
        doc.Print(&printer);
        Buffer buffer(printer.CStr(), printer.CStrSize());
        file.write(buffer);*/
    }
}
