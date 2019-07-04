#include "TestLevel.h"
#include "MathUtils.h"

class TestApplication:public Application {
private:
    Level* testLevel = nullptr;

public:
    void onInit() {
        testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);

        Renderer.ClearColor = &makeColor(0xff7f7f7f);
    }

    void onUninit() {
        LevelManager.setLevel(nullptr);
        delete testLevel;
    }
};
