#pragma once

#include "ApplicationWindow.h"
#include "Settings.h"
#include "WindowList.h"
#include "application/FeatureCollection.h"

#include "core/Noncopyable.h"
#include "core/SharedPointer.h"
#include "core/Timer.h"

namespace Ghurund::Core {
    class Timer;
    class FunctionQueue;
}

namespace Ghurund {
    class Graphics;
    class Renderer;
    class ParameterManager;

    class Application:public Noncopyable {
    private:
        WindowList windows;
        Ghurund::FunctionQueue* functionQueue = nullptr;
        bool running = false;

        Settings settings;
        Graphics* graphics;

        ResourceManager* resourceManager;
        ParameterManager* parameterManager;
        Timer* timer;

        Renderer* renderer;

        FeatureCollection features;

        Status init();
        void handleMessages();
        void uninit();

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

    public:
        virtual ~Application() {}

        inline bool isRunning() {
            return running;
        }

        __declspec(property(get = isRunning)) bool Running;

        void run(const Settings* val = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        inline const Settings& getSettings() const {
            return settings;
        }

        __declspec(property(get = getSettings)) const Settings& Settings;

        inline WindowList& getWindows() {
            return windows;
        }

        __declspec(property(get = getWindows)) WindowList& Windows;

        FunctionQueue& getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

        inline Graphics& getGraphics() {
            return *graphics;
        }

        __declspec(property(get = getGraphics)) Graphics& Graphics;

        inline ResourceManager& getResourceManager() {
            return *resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

        inline ParameterManager& getParameterManager() {
            return *parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager& ParameterManager;

        inline Timer& getTimer() {
            return *timer;
        }

        __declspec(property(get = getTimer)) Timer& Timer;

        inline Renderer& getRenderer() {
            return *renderer;
        }

        __declspec(property(get = getRenderer)) Renderer& Renderer;

        inline FeatureCollection& getFeatures() {
            return features;
        }

        __declspec(property(get = getFeatures)) FeatureCollection& Features;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Application>();
}