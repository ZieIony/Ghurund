#include "ghe2dpch.h"
#include "SoundComponent2D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SoundComponent2D::GET_TYPE() {
		static auto PROPERTY_POSITION = Ghurund::Core::Property<SoundComponent2D, XMFLOAT2>("Position", &getPosition, &setPosition);
		static auto PROPERTY_VELOCITY = Ghurund::Core::Property<SoundComponent2D, XMFLOAT2>("Velocity", &getVelocity, &setVelocity);
		static auto PROPERTY_DIRECTION = Ghurund::Core::Property<SoundComponent2D, XMFLOAT2>("Direction", &getDirection, &setDirection);
		static auto PROPERTY_UP = Ghurund::Core::Property<SoundComponent2D, XMFLOAT2>("Up", &getUp, &setUp);

		static const Ghurund::Core::Type TYPE = TypeBuilder<SoundComponent2D>()
			.withProperty(PROPERTY_POSITION)
			.withProperty(PROPERTY_VELOCITY)
			.withProperty(PROPERTY_DIRECTION)
			.withProperty(PROPERTY_UP)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
