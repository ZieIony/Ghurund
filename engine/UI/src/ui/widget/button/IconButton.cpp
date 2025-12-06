#include "ghuipch.h"
#include "IconButton.h"

#include "core/reflection/UniqueProperty.h"

namespace Ghurund::UI {
    void IconButton::onLayoutChanged() {
        if (state) {
            state->InteractionHandler = nullptr;
            state->release();
            state = nullptr;
        }
        __super::onLayoutChanged();
        Control* layoutControl = layout.get();
        if (layoutControl) {
            setPointer(state, (Ghurund::UI::StateIndicator*)layoutControl->find("state"));
            if (state)
                state->InteractionHandler = &interactionHandler;
            //setPointer(drawableView, (Ghurund::UI::DrawableView*)layoutControl->find("drawableView"));
            updateProperties();
        }
    }

    const Ghurund::Core::Type& IconButton::GET_TYPE() {
       // static auto PROPERTY_DRAWABLE = UniqueProperty<IconButton, std::unique_ptr<Ghurund::UI::DrawableAttr>>("Drawable", (void(IconButton::*)(std::unique_ptr<Ghurund::UI::DrawableAttr>)) & setDrawable);
        static auto PROPERTY_TINT = UniqueProperty<IconButton, std::unique_ptr<ColorAttr>>("Tint", (void(IconButton::*)(std::unique_ptr<Ghurund::UI::ColorAttr>)) & setTint);
        static const Ghurund::Core::Type TYPE = TypeBuilder<IconButton>()
        //    .withProperty(PROPERTY_DRAWABLE)
            .withProperty(PROPERTY_TINT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
 }