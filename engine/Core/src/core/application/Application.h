#pragma once

#include "Settings.h"
#include "WindowCollection.h"

#include "core/feature/FeatureProvider.h"
#include "core/Noncopyable.h"
#include "core/Timer.h"
#include "core/threading/FunctionQueue.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Core {
    class Application:public Noncopyable {
    private:
        WindowCollection windows;
        FunctionQueue functionQueue;
        bool running = false;

        Settings settings;

        ResourceManager resourceManager;
        Timer timer;

        FeatureProvider features = *this;

        void init();
        void uninit();

        /*
        * returns true if the app should stop handling messages and quit
        */
        bool handleMessages();

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

    public:
        virtual ~Application() {
            uninit();
        }

        inline bool isRunning() {
            return running;
        }

        __declspec(property(get = isRunning)) bool Running;

        void run(const Settings* val = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        // not null
        inline const Settings* getSettings() const {
            return &settings;
        }

        __declspec(property(get = getSettings)) const Settings* Settings;

        // not null
        inline WindowCollection* getWindows() {
            return &windows;
        }

        __declspec(property(get = getWindows)) WindowCollection* Windows;

        // not null
        FunctionQueue* getFunctionQueue() {
            return &functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue* FunctionQueue;

        // not null
        inline ResourceManager* getResourceManager() {
            return &resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager* ResourceManager;

        // not null
        inline Timer* getTimer() {
            return &timer;
        }

        __declspec(property(get = getTimer)) Timer* Timer;

        // not null
        inline FeatureProvider* getFeatures() {
            return &features;
        }

        __declspec(property(get = getFeatures)) FeatureProvider* Features;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Application>();
}