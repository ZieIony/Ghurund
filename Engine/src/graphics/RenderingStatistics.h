#pragma once

#include "editor/ObservableObject.h"
#include "application/Timer.h"

namespace Ghurund {
    class RenderingStatistics:public ObservableObject {
        friend class DrawableComponent;
		friend class GraphicsSystem;

    private:
        float renderingTime = 0;
        size_t modelsCulled = 0;
        size_t modelsRendered = 0;
        size_t trianglesRendered = 0;
        size_t materialChanges = 0;

        Timer timer;

    public:
        float getRenderingTime() const {
            return renderingTime;
        }

        __declspec(property(get = getRenderingTime)) float RenderingTime;

        size_t getModelsCulled() const {
            return modelsCulled;
        }

        __declspec(property(get = getModelsCulled)) size_t ModelsCulled;

        size_t getModelsRendered() const {
            return modelsRendered;
        }

        __declspec(property(get = getModelsRendered)) size_t ModelsRendered;

        size_t getTrianglesRendered() const {
            return trianglesRendered;
        }

        __declspec(property(get = getTrianglesRendered)) size_t TrianglesRendered;

        size_t getMaterialChanges() const {
            return materialChanges;
        }

        __declspec(property(get = getMaterialChanges)) size_t MaterialChanges;

        void startFrame() {
            renderingTime = 0;
            modelsCulled = 0;
            modelsRendered = 0;
            trianglesRendered = 0;
            materialChanges = 0;
            timer.tick();
        }

        void finishFrame() {
            timer.tick();
            renderingTime += timer.FrameTime;
            notifyObjectChanged();
        }
    };
}