#include "RigidBodyComponent.h"

namespace Ghurund {
	const Ghurund::Type& RigidBodyComponent::TYPE = Ghurund::Type([]() {return nullptr; }, "RigidBodyComponent");
}