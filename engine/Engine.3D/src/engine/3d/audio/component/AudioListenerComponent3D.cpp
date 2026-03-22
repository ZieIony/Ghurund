#include "ghe3dpch.h"
#include "AudioListenerComponent3D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& AudioListenerComponent3D::GET_TYPE() {
        static auto PROPERTY_POSITION = Ghurund::Core::Property<AudioListenerComponent3D, XMFLOAT3>("Position", &getPosition, &setPosition);
        static auto PROPERTY_VELOCITY = Ghurund::Core::Property<AudioListenerComponent3D, XMFLOAT3>("Velocity", &getVelocity, &setVelocity);
        static auto PROPERTY_DIRECTION = Ghurund::Core::Property<AudioListenerComponent3D, XMFLOAT3>("Direction", &getDirection, &setDirection);
        static auto PROPERTY_UP = Ghurund::Core::Property<AudioListenerComponent3D, XMFLOAT3>("Up", &getUp, &setUp);

        static const Ghurund::Core::Type TYPE = TypeBuilder<AudioListenerComponent3D>()
            .withProperty(PROPERTY_POSITION)
            .withProperty(PROPERTY_VELOCITY)
            .withProperty(PROPERTY_DIRECTION)
            .withProperty(PROPERTY_UP)
            .withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
