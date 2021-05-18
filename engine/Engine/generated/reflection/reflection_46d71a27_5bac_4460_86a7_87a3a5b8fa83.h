#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_46d71a27_5bac_4460_86a7_87a3a5b8fa83 protected:\
static const Ghurund::Type& GET_TYPE() {\
static auto PROPERTY_CLEARCOLOR = Ghurund::TypedProperty<Renderer, const XMFLOAT4*>("const XMFLOAT4*", "ClearColor", (XMFLOAT4*(Renderer::*)())&getClearColor, (void(Renderer::*)(const XMFLOAT4*))&setClearColor);\
static auto PROPERTY_STATISTICS = Ghurund::TypedProperty<Renderer, RenderingStatistics&>("RenderingStatistics&", "Statistics", (RenderingStatistics&(Renderer::*)())&getStatistics);\
\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<Renderer>();\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "Renderer")\
.withProperty(PROPERTY_CLEARCOLOR)\
.withProperty(PROPERTY_STATISTICS)\
.withConstructor(CONSTRUCTOR)\
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
