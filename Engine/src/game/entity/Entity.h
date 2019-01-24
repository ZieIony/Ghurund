#pragma once

#include "collection/String.h"
#include "core/NamedObject.h"
#include "game/entity/TransformedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/INotifyPropertyChanged.h"
#include "resource/Resource.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class RenderingBatch;

    class Entity: public Resource, public NamedObject, public ParameterProvider, public ObservableObject {
    public:
        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) = 0;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            return false;
        }
    };
}