#pragma once

#include "engine/2d/scene/Entity2D.h"
#include "engine/audio/sound/Sound.h"
#include <engine/2d/audio/component/AudioListenerComponent2D.h>
#include <engine/2d/audio/component/SoundComponent2D.h>
#include <engine/2d/graphics/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/graphics/sprite/SpriteAnimationSet.h>
#include <engine/2d/scene/camera/CameraComponent2D.h>

namespace Demo {
	using namespace Ghurund::Engine::_2D;

	class Captain:public Entity2D {
	private:
		IntrusivePointer<CameraComponent2D> cameraComponent;
		IntrusivePointer<SpriteAnimationSet> animationSet;
		IntrusivePointer<AnimatedSpriteComponent> captainSprite;
		IntrusivePointer<Sound> thudSound;
		IntrusivePointer<AudioListenerComponent2D> audioListenerComponent;
		IntrusivePointer<SoundComponent2D> soundComponent;

	protected:
		virtual CoroutineTask<void> onInit() override;;

	public:
		Captain(World2D& world):Entity2D(world) {}

		inline void playSound() {
			thudSound->play();
		}

		virtual void update(const Timer& timer) override;
	};
}
