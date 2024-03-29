#pragma once

#include "DrawableComponent.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/mesh/ConeMesh.h"

namespace Ghurund {
    class DrawableComponents {
    private:
        DrawableComponents() = delete;

    public:
        static DrawableComponent* makeCube(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material);
        static DrawableComponent* makePlane(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material, unsigned int detail = 1);
        static DrawableComponent* makeSphere(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material);
        static DrawableComponent* makeCone(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material);
        static DrawableComponent* makeQuad(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material);
    };
}