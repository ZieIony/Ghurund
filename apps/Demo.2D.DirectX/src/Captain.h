#pragma once

#include "engine/2d/scene/Entity2D.h"
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/graphics/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/graphics/sprite/SpriteAnimationSet.h>
#include <engine/2d/scene/camera/Camera2D.h>
#include <engine/2d/scene/camera/CameraComponent2D.h>

namespace Demo {
	using namespace Ghurund::Engine::_2D;

	class Captain:public Entity2D {
	private:
		IntrusivePointer<CameraComponent2D> cameraComponent;
		IntrusivePointer<SpriteAnimationSet> animationSet;
		IntrusivePointer<AnimatedSpriteComponent> captainSprite;

	protected:
		virtual CoroutineTask<void> onInit() override {
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

			captainCapsule->Components.add(captainSprite.get());
			captainCapsule->Components.add(cameraComponent.get());
			RootComponent = captainCapsule.get();

			co_await __super::onInit();
		};

	public:
		Captain(World2D& world):Entity2D(world) {}
	};
}
