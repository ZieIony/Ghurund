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
		frameTime = (float)frameTicks / frequency.QuadPart;
		frameTimeMs = (uint32_t)(frameTicks / fqMs);
		frameTimeNs = (uint64_t)(frameTicks / fqNs);

		uint64_t ticks = currentFrame.QuadPart - startFrame.QuadPart;
		time = (double)ticks / frequency.QuadPart;
		timeMs = (uint32_t)(ticks / fqMs);
		timeNs = (uint64_t)(ticks / fqNs);

		scaledFrameTime = std::min(frameTime * timeScale, maxFrameTime);
		scaledTime += scaledFrameTime;

		if (fpsFrames == frameWindow) {
			fps = fpsFrames / fpsTime;
			fpsTime = 0;
			fpsFrames = 0;
		}
		fpsFrames++;
		fpsTime += frameTime;
	}
}
