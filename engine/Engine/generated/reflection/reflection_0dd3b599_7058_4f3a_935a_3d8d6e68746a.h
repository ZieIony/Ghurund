#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_0dd3b599_7058_4f3a_935a_3d8d6e68746a protected:\
static const Ghurund::Type& GET_TYPE() {\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "Feature")\
.withModifier(TypeModifier::ABSTRACT)\
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
