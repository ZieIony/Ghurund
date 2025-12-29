#include "ghepch.h"
#include "TextureInput.h"

#include "engine/parameter/TextureParameter.h"

namespace Ghurund::Engine {
	TextureParameter* TextureInput::makeParameter() const {
		return ghnew TextureParameter(name);
	}
}