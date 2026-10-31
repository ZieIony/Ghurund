#include "ghcpch.h"
#include "Timer.h"

namespace Ghurund::Core {
	Timer::Timer() {
		QueryPerformanceCounter(&startFrame);
		currentFrame = startFrame;
		QueryPerformanceFrequency(&frequency);
		fqMs = frequency.QuadPart / 1000.0;
		fqNs = frequency.QuadPart / 1000000.0;
	}

	void Timer::tick() {
		LARGE_INTEGER prevFrame = currentFrame;
		QueryPerformanceCounter(&currentFrame);

		uint64_t frameTicks = currentFrame.QuadPart - prevFrame.QuadPart;
		frameTime.value = (float)frameTicks / frequency.QuadPart;
		frameTime.valueMs = (uint32_t)(frameTicks / fqMs);
		frameTime.valueNs = (uint64_t)(frameTicks / fqNs);

		uint64_t ticks = currentFrame.QuadPart - startFrame.QuadPart;
		appTime.value = (double)ticks / frequency.QuadPart;
		appTime.valueMs = (uint32_t)(ticks / fqMs);
		appTime.valueNs = (uint64_t)(ticks / fqNs);

		frameTime.scaledValue = std::min(frameTime.value * timeScale, maxFrameTime);
		appTime.scaledValue += frameTime.scaledValue;

		if (fpsFrames == frameWindow) {
			fps = fpsFrames / fpsTime;
			fpsTime = 0;
			fpsFrames = 0;
		}
		fpsFrames++;
		fpsTime += frameTime.value;

		frameTimeReminder += frameTime.scaledValue;
	}

	bool Timer::step() {
		if (timeScale == 0.0f)
			return false;

		if (frameTimeReminder >= fixedFrameTime) {
			frameTimeReminder -= fixedFrameTime;
			return true;
		}

		return false;
	}
}
