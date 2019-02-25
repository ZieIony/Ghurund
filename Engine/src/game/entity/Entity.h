#pragma once

#include "collection/String.h"
#include "core/NamedObject.h"
#include "game/entity/TransformedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/ObservableObject.h"
#include "resource/Resource.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class RenderStep;

    class Entity: public Resource, public NamedObject, public ParameterProvider, public ObservableObject {
    private:
        bool selectable;

    public:
        virtual void flatten(RenderStep &step, XMFLOAT4X4 &transformation) = 0;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir, float &dist) {
            return false;
        }

        void setSelectable(bool selectable) {
            this->selectable = selectable;
        }

        bool isSelectable() const {
            return selectable;
        }

        __declspec(property(get = isSelectable, put = setSelectable)) bool Selectable;
    };
}