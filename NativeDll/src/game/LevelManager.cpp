#include "game/LevelManager.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) LevelManager *LevelManager_new() {
    return new LevelManager();
}

extern "C" __declspec(dllexport) void LevelManager_delete(LevelManager *_this) {
    delete _this;
}

extern "C" __declspec(dllexport) void LevelManager_setLevel(LevelManager *_this, Level *level) {
    _this->setLevel(level);
}

extern "C" __declspec(dllexport) void LevelManager_draw(LevelManager *_this, Renderer *renderer, ParameterManager *parameterManager) {
    _this->draw(*renderer, *parameterManager);
}

extern "C" __declspec(dllexport) Level *Level_new() {
    return new Level();
}

extern "C" __declspec(dllexport) void Level_delete(Level *_this) {
    delete _this;
}

