#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_08c20e05_8779_4620_93c4_d7dbd043fcf2 protected:\
static const Ghurund::Type& GET_TYPE() {\
static auto PROPERTY_POSITION = Ghurund::TypedProperty<Audio, XMFLOAT3>("XMFLOAT3", "Position", (XMFLOAT3(Audio::*)())&getPosition, (void(Audio::*)(XMFLOAT3))&setPosition);\
static auto PROPERTY_VELOCITY = Ghurund::TypedProperty<Audio, XMFLOAT3>("XMFLOAT3", "Velocity", (XMFLOAT3(Audio::*)())&getVelocity, (void(Audio::*)(XMFLOAT3))&setVelocity);\
static auto PROPERTY_DIRECTION = Ghurund::TypedProperty<Audio, XMFLOAT3>("XMFLOAT3", "Direction", (XMFLOAT3(Audio::*)())&getDirection, (void(Audio::*)(XMFLOAT3))&setDirection);\
static auto PROPERTY_UP = Ghurund::TypedProperty<Audio, XMFLOAT3>("XMFLOAT3", "Up", (XMFLOAT3(Audio::*)())&getUp, (void(Audio::*)(XMFLOAT3))&setUp);\
\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<Audio>();\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund::Audio", "Audio")\
.withProperty(PROPERTY_POSITION)\
.withProperty(PROPERTY_VELOCITY)\
.withProperty(PROPERTY_DIRECTION)\
.withProperty(PROPERTY_UP)\
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
