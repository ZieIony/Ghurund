#pragma once

#include "collection/String.h"
#include "ParameterProvider.h"
#include "ParameterManager.h"
#include "resource/Resource.h"
#include "core/NamedObject.h"
#include "graphics/TransformedObject.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class RenderingBatch;

    class Entity: public Resource, public NamedObject, public ParameterProvider {
    public:
        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) = 0;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            return false;
        }
    };
}