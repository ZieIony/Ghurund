#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_c98597c1_bb96_4ddc_92c4_079c395065da protected:\
static const Ghurund::Type& GET_TYPE() {\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "ScriptEngine")\
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
