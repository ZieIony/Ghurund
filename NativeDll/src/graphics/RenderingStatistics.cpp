#include "graphics/RenderingStatistics.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) float RenderingStatistics_getRenderingTime(RenderingStatistics *_this) {
    return _this->RenderingTime;
}

extern "C" __declspec(dllexport) unsigned int RenderingStatistics_getModelsCulled(RenderingStatistics *_this) {
    return _this->ModelsCulled;
}

extern "C" __declspec(dllexport) unsigned int RenderingStatistics_getModelsRendered(RenderingStatistics *_this) {
    return _this->ModelsRendered;
}

extern "C" __declspec(dllexport) unsigned int RenderingStatistics_getTrianglesRendered(RenderingStatistics *_this) {
    return _this->TrianglesRendered;
}

extern "C" __declspec(dllexport) unsigned int RenderingStatistics_getMaterialChanges(RenderingStatistics *_this) {
    return _this->MaterialChanges;
}

extern "C" __declspec(dllexport) void RenderingStatistics_reset(RenderingStatistics *_this) {
    _this->reset();
}
