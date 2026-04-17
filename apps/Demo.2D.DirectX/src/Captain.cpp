#include "Captain.h"

#include "core/application/Application.h"
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/scene/camera/Camera2D.h>
#include "engine/2d/World2D.h"

namespace Demo {
	CoroutineTask<void> Captain::onInit() {
		auto captainCapsule = IntrusivePointer(makeComponent<CapsuleComponent2D>());
		co_await captainCapsule->init();
		captainCapsule->Type = BodyType::DYNAMIC;
		captainCapsule->IsRotationFixed = true;
		captainCapsule->Size = { 0.35f, 0.7f };

		captainSprite = IntrusivePointer(makeComponent<AnimatedSpriteComponent>());
		co_await captainSprite->init();

		animationSet = co_await World.app->ResourceManager.load<SpriteAnimationSet>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/captain.xml"));
		captainSprite->Animation = animationSet->get(animationSet->find(L"idle"));

		captainSprite->Position = { 0, -0.025f * 2.0f };
		captainSprite->Size = { 1.6f, 1 };

		cameraComponent = IntrusivePointer(makeComponent<CameraComponent2D>());
		cameraComponent->Camera->ViewSize = { 8, 6 };
		cameraComponent->Camera->setPositionUp({ 0, 0 });
		World.scene->Camera = cameraComponent->Camera;

		thudSound = co_await World.app->ResourceManager.load<Sound>(ResourceManager::ENGINE_LIB / FilePath(L"test/sounds/thud.wav"));
		audioListenerComponent = IntrusivePointer(makeComponent<AudioListenerComponent2D>());
		World.audioWorld->AudioListener = audioListenerComponent.get();

		soundComponent = IntrusivePointer(makeComponent<SoundComponent2D>());
		soundComponent->Sound = thudSound.get();
		World.audioWorld->soundComponents.add(soundComponent);

		captainCapsule->Components.add(captainSprite.get());
		captainCapsule->Components.add(cameraComponent.get());
		captainCapsule->Components.add(audioListenerComponent.get());
		RootComponent = captainCapsule.get();

		co_await __super::onInit();
	}
	
	void Captain::update(const Timer& timer) {
		__super::update(timer);
		// TODO: position update should be automatic
		audioListenerComponent->Position = RootComponent->Position;
		audioListenerComponent->Direction = { RootComponent->Scale.x, 0 };
	}
}
