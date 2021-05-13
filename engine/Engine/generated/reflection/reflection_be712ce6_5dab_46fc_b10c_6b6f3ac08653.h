#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_be712ce6_5dab_46fc_b10c_6b6f3ac08653 protected:\
static const Ghurund::Type& GET_TYPE() {\
static auto PROPERTY_GRAPHICS2D = Ghurund::TypedProperty<UIFeature, Ghurund::Graphics2D&>("Ghurund::Graphics2D&", "Graphics2D", (Ghurund::Graphics2D&(UIFeature::*)())&getGraphics2D);\
static auto PROPERTY_THEME = Ghurund::TypedProperty<UIFeature, Ghurund::UI::Theme*>("Ghurund::UI::Theme*", "Theme", (Ghurund::UI::Theme*(UIFeature::*)())&getTheme, (void(UIFeature::*)(Ghurund::UI::Theme*))&setTheme);\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "UIFeature")\
.withProperty(PROPERTY_GRAPHICS2D)\
.withProperty(PROPERTY_THEME)\
.withSupertype(__super::GET_TYPE());\
\
return TYPE;\
}\
\
public:\
inline static const Ghurund::Type& TYPE = GET_TYPE();\
\
virtual const Ghurund::Type& getType() const override {\
return TYPE;\
}
