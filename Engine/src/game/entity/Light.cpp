#include "Light.h"
#include "graphics/RenderStep.h"

namespace Ghurund {
    void Light::queueDraw(RenderStep &step, XMFLOAT4X4 &transformation) {
        step.addLight(*this);
    }
}
