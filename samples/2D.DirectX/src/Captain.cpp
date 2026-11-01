#include "Common.h"
#include <Windows.h>

#include "Captain.h"

#include "CaptainStates.h"

#include "engine/2d/World2D.h"
#include <core/resource/ResourceManager.h>
#include <engine/2d/graphics/sprite/animation/SpriteAnimation.h>
#include <engine/2d/graphics/sprite/animation/SpriteAnimationSet.h>
#include <engine/2d/scene/camera/Camera2D.h>
#include <engine/animation/AnimatorState.h>
#include <engine/2d/scene/camera/CameraComponent2D.h>
#include <engine/2d/graphics/sprite/SpriteComponent.h>
#include <engine/2d/physics/visualization/VisualizationComponent2D.h>

namespace Sample {
	CoroutineTask<void> Captain::init(PhysicsSystem2D& physicsSystem, ResourceManager& resourceManager, IGPUMemoryManager& memoryManager, World2D& world) {
		addComponent<TransformComponent2D>();

		auto& capsuleComponent = addComponent<RigidBodyComponent2D>();
		capsuleComponent.init(physicsSystem, ShapeType::CAPSULE);
		capsuleComponent.BodyType = BodyType::DYNAMIC;
		capsuleComponent.IsRotationFixed = true;
		capsuleComponent.setSize(0.4f, 0.7f);
		auto& visComponent = addComponent<VisualizationComponent2D>();
		visComponent.init(memoryManager, capsuleComponent);

		{
			auto& captainSprite = addComponent<SpriteComponent>();
			captainSprite.init(memoryManager);
			captainSprite.offset = { 0, -0.05f };
			captainSprite.size = { 1.6f, 1 };
		}

		{
			auto& captainAnimation = addComponent<SpriteAnimationComponent>();

			auto animationSet = co_await resourceManager.load<SpriteAnimationSet>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/images/captain.xml"));
			captainAnimation.Animation = animationSet->get(animationSet->find(L"idle"));

			auto animator = makeIntrusive<SpriteAnimator>();
			animator->putState(makeIntrusive<AnimatorState<SpriteAnimation>>(L"idle", animationSet->get(L"idle")).get());
			animator->putState(makeIntrusive<AnimatorState<SpriteAnimation>>(L"walking", animationSet->get(L"walking")).get());
			animator->putTransition(makeIntrusive<CaptainSTIdleWalking>(*this).get());
			animator->putTransition(makeIntrusive<CaptainSTWalkingIdle>(*this).get());
			animator->reset(L"idle");

			captainAnimation.Animator = animator.get();
		}

		auto& cameraComponent = addComponent<CameraComponent2D>();
		cameraComponent.Camera->ViewSize = { 8, 6 };
		cameraComponent.Camera->setPositionUp({ 0, 0 });
		world.Scene.Camera = cameraComponent.Camera;

		auto thudSound = co_await resourceManager.load<Sound>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/sounds/thud.wav"));
		auto& audioListenerComponent = addComponent<AudioListenerComponent2D>();
		//world.AudioSystem->AudioListener = audioListenerComponent;

		auto& soundComponent = addComponent<SoundComponent2D>();
		soundComponent.Sound = thudSound.get();
		//World.AudioSystem->soundComponents.add(soundComponent);
	}

	void Captain::update(const Timer& timer) {
		// TODO: position update should be automatic
		//audioListenerComponent->Position = Transform.Position;
		//audioListenerComponent->Direction = { Transform.Scale.x, 0 };
	}
}
