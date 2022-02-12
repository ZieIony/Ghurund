#include "ghuipch.h"
#include "ColorView.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"
#include <ui/Binding.h>

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ColorView>();
        static auto PROPERTY_COLOR = Property<ColorView, const ColorAttr&>("Color", (const ColorAttr & (ColorView::*)()) & getColor, (void(ColorView::*)(const ColorAttr&)) & setColor);

        static const Ghurund::Core::Type& TYPE = TypeBuilder<ColorView>(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
            .withConstructor(CONSTRUCTOR)
            .withProperty(PROPERTY_COLOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ColorView::onDraw(ICanvas& canvas) {
        const Ghurund::UI::Color& c = color->getValue(*this);
        if (c.A > 0.0f)
            canvas.fillRect(0, 0, Size.width, Size.height, c);
    }

    void ColorView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr) {
            /*try {
                Binding binding = Binding::parse(colorAttr->Value());
                Array<AString> path = binding.Path;
                size_t propIndex = Type.Properties.find([&](BaseProperty* prop) {
                    return prop->Name == "Color";
                });
                if (propIndex != Type.Properties.Size) {
                    BaseProperty* targetProperty = Type.Properties[propIndex];
                    Control* result = resolvePath(path);
                    if (result) {
                        size_t sourcePropIndex = result->Type.Properties.find([&](BaseProperty* prop) {
                            return prop->Name == binding.PropertyName;
                        });
                        if (sourcePropIndex != result->Type.Properties.Size) {
                            BaseProperty* sourceProperty = result->Type.Properties[sourcePropIndex];
                            if (sourceProperty->Type == targetProperty->Type) { // TODO: extends
                                sourceProperty->getRaw(result, [&](void* val) {
                                    targetProperty->setRaw(this, val);
                                });
                            } else {
                                Logger::log(LogType::WARNING, std::format(_T("Invalid binding property type: '{}'.\n"), AString(colorAttr->Value())).c_str());
                            }
                        } else {
                            Logger::log(LogType::WARNING, std::format(_T("Invalid binding source: '{}'.\n"), AString(colorAttr->Value())).c_str());
                        }
                    } else {
                        Logger::log(LogType::WARNING, std::format(_T("Invalid binding path: '{}'.\n"), AString(colorAttr->Value())).c_str());
                    }
                }
            } catch (InvalidParamException e) {*/
                auto color = loader.loadColor(colorAttr->Value());
                if (color) {
                    Color = *color;
                    delete color;
                } else {
                    Logger::log(LogType::WARNING, std::format(_T("Invalid color value: '{}'.\n"), AString(colorAttr->Value())).c_str());
                }
            //}
        }
    }

    void ColorViewBackgroundStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_BACKGR0UND);
    }

    void ColorViewControlStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_CONTROL);
    }

    void ColorViewAccentStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_ACCENT);
    }
}
