#include "TransformComponent.h"

namespace Ghurund {
	const Ghurund::Type& TransformComponent::TYPE = Ghurund::Type([]() {return ghnew TransformComponent(); }, "TransformComponent");
}