#include "game/LevelManager.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) LevelManager *LevelManager_new() {
    return new LevelManager();
}

extern "C" __declspec(dllexport) void LevelManager_setLevel(LevelManager *_this, Level *level) {
    _this->setLevel(level);
}

extern "C" __declspec(dllexport) void LevelManager_draw(LevelManager *_this, CommandList *commandList, ParameterManager *parameterManager) {
 //   _this->draw(*commandList, *parameterManager);
}

extern "C" __declspec(dllexport) Level *Level_new() {
    return new Level();
}

extern "C" __declspec(dllexport) void Level_setCamera(Level *_this, Camera *camera) {
    _this->setCamera(camera);
}

extern "C" __declspec(dllexport) void Level_setScene(Level *_this, Scene *scene) {
    _this->setScene(scene);
}

