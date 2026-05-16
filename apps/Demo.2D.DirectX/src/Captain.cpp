#include "Captain.h"

#include "CaptainStates.h"

#include "core/application/Application.h"
#include "engine/2d/World2D.h"
#include <core/resource/ResourceManager.h>
#include <engine/2d/graphics/sprite/SpriteAnimation.h>
#include <engine/2d/graphics/sprite/SpriteAnimationSet.h>
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/scene/camera/Camera2D.h>
#include <engine/animation/AnimatorState.h>

namespace Demo {
	CoroutineTask<void> Captain::onInit() {
		capsuleComponent = IntrusivePointer(makeComponent<CapsuleComponent2D>());
		co_await capsuleComponent->init();
		capsuleComponent->BodyType = BodyType::DYNAMIC;
		capsuleComponent->IsRotationFixed = true;
		capsuleComponent->setHeightRadius(0.7f, 0.2f);

		captainSprite = IntrusivePointer(makeComponent<AnimatedSpriteComponent>());
		co_await captainSprite->init();

		auto animationSet = co_await World.app.ResourceManager.load<SpriteAnimationSet>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/captain.xml"));
		captainSprite->Animation = animationSet->get(animationSet->find(L"idle"));

		animator = makeIntrusive<SpriteAnimator>();
		animator->putState(makeIntrusive<AnimatorState<SpriteAnimation>>(L"idle", animationSet->get(L"idle")).get());
		animator->putState(makeIntrusive<AnimatorState<SpriteAnimation>>(L"walking", animationSet->get(L"walking")).get());
		animator->putTransition(makeIntrusive<CaptainSTIdleWalking>(*this).get());
		animator->putTransition(makeIntrusive<CaptainSTWalkingIdle>(*this).get());
		animator->reset(L"idle");

		captainSprite->Animator = animator.get();
		captainSprite->Offset = { 0, -0.05f };
		captainSprite->Size = { 1.6f, 1 };

		cameraComponent = IntrusivePointer(makeComponent<CameraComponent2D>());
		cameraComponent->Camera->ViewSize = { 8, 6 };
		cameraComponent->Camera->setPositionUp({ 0, 0 });
		World.Scene.Camera = cameraComponent->Camera;

		thudSound = co_await World.app.ResourceManager.load<Sound>(ResourceManager::ENGINE_LIB / FilePath(L"test/sounds/thud.wav"));
		audioListenerComponent = IntrusivePointer(makeComponent<AudioListenerComponent2D>());
		World.AudioSystem->AudioListener = audioListenerComponent.get();

		soundComponent = IntrusivePointer(makeComponent<SoundComponent2D>());
		soundComponent->Sound = thudSound.get();
		World.AudioSystem->soundComponents.add(soundComponent);

		Components.add(captainSprite.get());
		Components.add(cameraComponent.get());
		Components.add(audioListenerComponent.get());
		Components.add(capsuleComponent.get());

		co_await __super::onInit();
	}

	Captain::Captain(World2D& world):Entity2D(world) {
	}
	
	void Captain::update(const Timer& timer) {
		__super::update(timer);
		// TODO: position update should be automatic
		audioListenerComponent->Position = Transform.Position;
		audioListenerComponent->Direction = { Transform.Scale.x, 0 };
	}
}
