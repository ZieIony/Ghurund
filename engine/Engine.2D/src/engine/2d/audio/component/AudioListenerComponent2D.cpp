#include "ghe2dpch.h"
#include "AudioListenerComponent2D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& AudioListenerComponent2D::GET_TYPE() {
        static auto PROPERTY_POSITION = Ghurund::Core::Property<AudioListenerComponent2D, XMFLOAT2>("Position", &getPosition, &setPosition);
        static auto PROPERTY_VELOCITY = Ghurund::Core::Property<AudioListenerComponent2D, XMFLOAT2>("Velocity", &getVelocity, &setVelocity);
        static auto PROPERTY_DIRECTION = Ghurund::Core::Property<AudioListenerComponent2D, XMFLOAT2>("Direction", &getDirection, &setDirection);
        static auto PROPERTY_UP = Ghurund::Core::Property<AudioListenerComponent2D, XMFLOAT2>("Up", &getUp, &setUp);

        static const Ghurund::Core::Type TYPE = TypeBuilder<AudioListenerComponent2D>()
            .withProperty(PROPERTY_POSITION)
            .withProperty(PROPERTY_VELOCITY)
            .withProperty(PROPERTY_DIRECTION)
            .withProperty(PROPERTY_UP)
            .withSupertype(__super::GET_TYPE());

		return TYPE;
	}
    
    AudioListenerComponent2D::AudioListenerComponent2D(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {
        memset(&listener, 0, sizeof(listener));
        listener.Direction = { 1, 0, 0 };
        listener.Up = { 0, 1, 0 };
    }
}
