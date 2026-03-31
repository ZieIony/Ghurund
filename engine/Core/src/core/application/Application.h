#pragma once

#include "Settings.h"
#include "WindowCollection.h"

#include "core/feature/FeatureProvider.h"
#include "core/object/Initializable.h"
#include "core/object/Noncopyable.h"
#include "core/Timer.h"
#include "core/resource/ResourceManager.h"
#include "core/coroutine/CoroutineScheduler.h"

namespace Ghurund::Core {
	class Application:public Noncopyable, public Initializable {
	private:
		Timer timer;
		WindowCollection windows;

		CoroutineThreadPool threadPool = CoroutineThreadPool(4);
		CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);

		bool running = false;

		Settings settings;

		ResourceManager resourceManager = coroutineScheduler;

		FeatureProvider features = *this;

		/*
		* returns true if the app should stop handling messages and quit
		*/
		bool handleMessages();

		void uninitApplication();

		Application& operator=(const Application& other) = delete;

	protected:
		virtual void onInit();

		virtual void onUninit();

	public:
		Application() {
			CoInitialize(nullptr);
			OleInitialize(nullptr);
		}

		virtual ~Application() {
			if (IsInitialized)
				uninitApplication();

			// TODO: cancel and destroy coroutines
			OleUninitialize();
			CoUninitialize();
		}

		inline bool isRunning() {
			return running;
		}

		__declspec(property(get = isRunning)) bool Running;

		void run(const Settings* val = nullptr);

		inline void quit() {
			PostQuitMessage(0);
		}

		inline Settings getSettings() const {
			return settings;
		}

		__declspec(property(get = getSettings)) Settings Settings;

		inline WindowCollection& getWindows() {
			return windows;
		}

		__declspec(property(get = getWindows)) WindowCollection& Windows;

		CoroutineScheduler& getCoroutineScheduler() {
			return coroutineScheduler;
		}

		__declspec(property(get = getCoroutineScheduler)) CoroutineScheduler& CoroutineScheduler;

		inline ResourceManager& getResourceManager() {
			return resourceManager;
		}

		__declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

		inline Timer& getTimer() {
			return timer;
		}

		__declspec(property(get = getTimer)) Timer& Timer;

		inline FeatureProvider& getFeatures() {
			return features;
		}

		__declspec(property(get = getFeatures)) FeatureProvider& Features;
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Application>();
}