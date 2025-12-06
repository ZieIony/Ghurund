#pragma once

#include "core/Color.h"
#include "core/Colors.h"
#include "engine/graphics/texture/ITexture.h"
#include "engine/parameter/TextureParameter.h"
#include "ui/control/Control.h"
#include "ui/style/PointerAttrProperty.h"
#include "ui/style/TextureAttr.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ImageView:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ImageView::GET_TYPE();
#pragma endregion

    private:
        // TODO: maybe this should be Image*?
        PointerAttrProperty<TextureAttr, ITexture> image;
        TextureParameter* imageParameter;
        Color tint = Colors::WHITE;
        Float4Parameter* tintParameter;

    protected:
        virtual void onMaterialChanged() override {
            if (Material) {
                imageParameter = (TextureParameter*)Material->Parameters.get("image");
                imageParameter->Value = image.get();
                tintParameter = (Float4Parameter*)Material->Parameters.get("tint");
                tintParameter->Value = tint.toVector();
            } else {
                tintParameter = nullptr;
            }
        }

        virtual void onThemeChanged() override {
            const UI::Theme* theme = Theme;
            if (theme) {
                image.resolve(*theme);
                if (imageParameter)
                    imageParameter->Value = image.get();
            }
        }

    public:
        inline void setImage(std::unique_ptr<TextureAttr> image) {
            this->image.set(std::move(image));
            if (imageParameter)
                imageParameter->Value = this->image.get();
        }

        __declspec(property(put = setImage)) std::unique_ptr<TextureAttr> Image;

        inline void setTint(const Color& tint) {
            this->tint = tint;
            if(tintParameter)
                tintParameter->Value = tint.toVector();
        }

        inline const Color& getTint() const {
            return tint;
        }

        __declspec(property(get = getTint, put = setTint)) const Color& Tint;
    };
}