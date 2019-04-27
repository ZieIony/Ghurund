#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class SphereMesh: public Mesh {
    protected:
        Status init(Graphics &graphics, CommandList &commandList, unsigned int detail = 2);

        virtual PxGeometry getGeometry() override {
            return PxSphereGeometry(0.5);
        }
    };
}