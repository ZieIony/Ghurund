#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_877c7fb3_5824_4c07_b617_0772d5149da1 protected:\
static const Ghurund::Type& GET_TYPE() {\
static auto PROPERTY_SWAPCHAIN = Ghurund::TypedProperty<ApplicationWindow, Ghurund::SwapChain&>("Ghurund::SwapChain&", "SwapChain", (Ghurund::SwapChain&(ApplicationWindow::*)())&getSwapChain);\
static auto PROPERTY_LAYERS = Ghurund::TypedProperty<ApplicationWindow, LayerList&>("LayerList&", "Layers", (LayerList&(ApplicationWindow::*)())&getLayers);\
static auto PROPERTY_APPLICATION = Ghurund::TypedProperty<ApplicationWindow, Ghurund::Application&>("Ghurund::Application&", "Application", (Ghurund::Application&(ApplicationWindow::*)())&getApplication);\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "ApplicationWindow")\
.withProperty(PROPERTY_SWAPCHAIN)\
.withProperty(PROPERTY_LAYERS)\
.withProperty(PROPERTY_APPLICATION)\
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
