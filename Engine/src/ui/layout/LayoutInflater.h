#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"
#include "core/collection/PointerMap.h"

#include "json.hpp"

namespace Ghurund::UI {
    using namespace nlohmann;

    class LayoutInflater {
    private:
        Map<std::string, std::function<Control*(LayoutInflater&, json&)>> typeHandlers;
        PointerMap<String, GdiImage*> images;

        void registerBasicTypes();

    public:
        LayoutInflater() {
            registerBasicTypes();
        }

        void registerType(const tchar* name, std::function<Control*(LayoutInflater&, json&)> handler) {
            typeHandlers.set(name, handler);
        }

        Control* load(const char* jsonString) {
            json jsonData = json::parse(jsonString, nullptr, false, true);
            if (jsonData.is_null())
                return nullptr;
            return loadObject(jsonData);
        }

        Control* loadObject(json& json) {
            auto& handler = typeHandlers.get(json["type"]);
            Control* control = handler(*this, json);
            return control;
        }

        List<Control*> loadArray(json& json) {
            List<Control*> array;
            for (auto j : json)
                array.add(loadObject(j));
            return array;
        }

        void loadChild(ControlContainer* group, json& json);

        void loadChildren(ControlGroup* group, json& json);

        void loadControl(Control* control, json& json);

        template <class Type>
        void loadGravity(Type* control, json& json) {
            if (json.contains("gravity")) {
                nlohmann::json& gravity = json["gravity"];
                if (gravity.is_object()) {
                    if (gravity.contains("horizontal")) {
                        nlohmann::json& horizontal = gravity["horizontal"];
                        if (horizontal.is_string()) {
                            if (horizontal == std::string("right")) {
                                control->Gravity.horizontal = Gravity::Horizontal::RIGHT;
                            } else if (horizontal == std::string("center")) {
                                control->Gravity.horizontal = Gravity::Horizontal::CENTER;
                            } else {
                                control->Gravity.horizontal = Gravity::Horizontal::LEFT;
                            }
                        }
                    }
                    if (gravity.contains("vertical")) {
                        nlohmann::json& vertical = gravity["vertical"];
                        if (vertical.is_string()) {
                            if (vertical == std::string("bottom")) {
                                control->Gravity.vertical = Gravity::Vertical::BOTTOM;
                            } else if (vertical == std::string("center")) {
                                control->Gravity.vertical = Gravity::Vertical::CENTER;
                            } else {
                                control->Gravity.vertical = Gravity::Vertical::TOP;
                            }
                        }
                    }
                }
            }
        }

        GdiImage* loadImage(const String& fileName) {
            if (images.contains(fileName))
                return images.get(fileName);
            GdiImage* image = ghnew GdiImage(fileName);
            images.set(fileName, image);
            image->release();
            return image;
        }
    };
}