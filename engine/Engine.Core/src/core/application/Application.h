#pragma once

#include "Settings.h"
#include "WindowList.h"
#include "FeatureCollection.h"

#include "core/Noncopyable.h"
#include "core/SharedPointer.h"
#include "core/Timer.h"
#include "core/threading/FunctionQueue.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Core {
    class Application:public Noncopyable {
    private:
        SystemWindowManager windowManager;
        WindowList windows = windowManager;
        FunctionQueue functionQueue;
        bool running = false;

        Settings settings;

        ResourceManager resourceManager;
        Timer timer;

        FeatureCollection features;

        void init();
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
            return functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

        inline ResourceManager& getResourceManager() {
            return resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

        inline Timer& getTimer() {
            return timer;
        }

        __declspec(property(get = getTimer)) Timer& Timer;

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