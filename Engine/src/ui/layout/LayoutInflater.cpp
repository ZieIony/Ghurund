#include "LayoutInflater.h"
#include "ui/control/Column.h"
#include "ui/control/ImageView.h"
#include "ui/control/Padding.h"
#include "ui/control/Row.h"
#include "ui/control/ScrollView.h"
#include "ui/control/Space.h"
#include "ui/control/Stack.h"
#include "ui/widget/TextButton.h"

namespace Ghurund::UI {
    void LayoutInflater::registerBasicTypes() {
        registerType(Stack::TYPE.Name, Stack::inflate);
        registerType(Row::TYPE.Name, Row::inflate);
        registerType(Column::TYPE.Name, Column::inflate);
        registerType(Space::TYPE.Name, Space::inflate);
        registerType(Padding::TYPE.Name, Padding::inflate);
        registerType(ScrollView::TYPE.Name, ScrollView::inflate);
        registerType(Surface::TYPE.Name, Surface::inflate);
        registerType(Button::TYPE.Name, Button::inflate);
        registerType(TextView::TYPE.Name, TextView::inflate);
        registerType(ImageView::TYPE.Name, ImageView::inflate);
        registerType(Border::TYPE.Name, Border::inflate);

        registerType(_T("TextButton"), [&](LayoutInflater& inflater, json& json) {
            Font* font = ghnew Font("Arial", 10);
            TextButton* button = ghnew TextButton(font);
            if (json.contains("text")) {
                nlohmann::json text = json["text"];
                if (text.is_string()) {
                    std::string textString = text;
                    button->Text = textString.c_str();
                }
            }
            loadControl(button, json);
            return button;
        });
    }

    void LayoutInflater::loadChild(ControlContainer* container, json& json) {
        if (json.contains("child")) {
            nlohmann::json& child = json["child"];
            if (child.is_object())
                container->Child = loadObject(child);
        }
    }

    void LayoutInflater::loadChildren(ControlGroup* group, json& json) {
        if (json.contains("children")) {
            nlohmann::json& children = json["children"];
            if (children.is_array()) {
                Array<Control*> array = loadArray(children);
                for (Control* c : array)
                    group->Children.add(c);
            }
        }
    }

    void LayoutInflater::loadControl(Control* control, json& json) {
        if (json.contains("width")) {
            nlohmann::json& width = json["width"];
            if (width.is_number()) {
                float widthFloat = width;
                control->PreferredSize.width = PreferredSize::Width(widthFloat);
            } else if (width.is_string()) {
                if (width == std::string("wrap")) {
                    control->PreferredSize.width = PreferredSize::Width::WRAP;
                } else if (width == std::string("fill")) {
                    control->PreferredSize.width = PreferredSize::Width::FILL;
                }
            }
        }
        if (json.contains("height")) {
            nlohmann::json& height = json["height"];
            if (height.is_number()) {
                float heightFloat = height;
                control->PreferredSize.height = PreferredSize::Height(heightFloat);
            } else if (height.is_string()) {
                if (height == std::string("wrap")) {
                    control->PreferredSize.height = PreferredSize::Height::WRAP;
                } else if (height == std::string("fill")) {
                    control->PreferredSize.height = PreferredSize::Height::FILL;
                }
            }
        }
    }
}