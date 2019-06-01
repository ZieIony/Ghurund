#include "Light.h"
#include "graphics/RenderStep.h"

namespace Ghurund {
    void Light::render(RenderStep &step, XMFLOAT4X4 &transformation) {
        step.addLight(*this);
    }
}
