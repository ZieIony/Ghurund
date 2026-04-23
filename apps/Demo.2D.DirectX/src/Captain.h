#pragma once

#include "engine/2d/scene/Entity2D.h"
#include "engine/audio/sound/Sound.h"
#include <engine/2d/audio/component/AudioListenerComponent2D.h>
#include <engine/2d/audio/component/SoundComponent2D.h>
#include <engine/2d/graphics/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/scene/camera/CameraComponent2D.h>
#include <engine/2d/graphics/sprite/SpriteAnimator.h>

namespace Demo {
	using namespace Ghurund::Engine::_2D;

	class Captain:public Entity2D {
	private:
		IntrusivePointer<SpriteAnimator> animator;
		IntrusivePointer<CameraComponent2D> cameraComponent;
		IntrusivePointer<CapsuleComponent2D> capsuleComponent;
		IntrusivePointer<AnimatedSpriteComponent> captainSprite;
		IntrusivePointer<Sound> thudSound;
		IntrusivePointer<AudioListenerComponent2D> audioListenerComponent;
		IntrusivePointer<SoundComponent2D> soundComponent;

	protected:
		virtual CoroutineTask<void> onInit() override;

	public:
		Captain(World2D& world);

		inline AnimatedSpriteComponent& getAnimatedSprite() {
			return captainSprite.ref();
		}

		__declspec(property(get = getAnimatedSprite)) AnimatedSpriteComponent& AnimatedSprite;

		inline CapsuleComponent2D& getCapsuleComponent() {
			return capsuleComponent.ref();
		}

		__declspec(property(get = getCapsuleComponent)) CapsuleComponent2D& CapsuleComponent;

		inline void playSound() {
			thudSound->play();
		}

		virtual void update(const Timer& timer) override;
	};
}
