#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_a03568f5_3f80_416f_aafa_4cf87e702942 protected:\
static const Ghurund::Type& GET_TYPE() {\
\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<Physics>();\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund::Physics", "Physics")\
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
