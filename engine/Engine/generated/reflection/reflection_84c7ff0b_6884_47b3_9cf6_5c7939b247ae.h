#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_84c7ff0b_6884_47b3_9cf6_5c7939b247ae protected:\
static const Ghurund::Type& GET_TYPE() {\
\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<Networking>();\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund::Net", "Networking")\
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
