#pragma once

#include "PropertyLoader.h"
#include "ui/control/DrawableView.h"

namespace Ghurund::UI {

    class ImageScaleModePropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<Ghurund::UI::ImageScaleMode>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            if (text == "crop") {
                auto scaleMode = ImageScaleMode::CROP;
                property.setRaw(&obj, &scaleMode);
            } else if (text == "fit") {
                auto scaleMode = ImageScaleMode::FIT;
                property.setRaw(&obj, &scaleMode);
            } else if (text == "none") {
                auto scaleMode = ImageScaleMode::NONE;
                property.setRaw(&obj, &scaleMode);
            } else if (text == "stretch") {
                auto scaleMode = ImageScaleMode::STRETCH;
                property.setRaw(&obj, &scaleMode);
            }
        }
    };
}