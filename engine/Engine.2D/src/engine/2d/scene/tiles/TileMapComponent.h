#pragma once

#include "TileMap.h"

#include "engine/2d/scene/component/Component2D.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class TileMapComponent:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TileMapComponent::GET_TYPE();
#pragma endregion

	private:
		TileMap* tileMap = nullptr;
		EventHandler<Resource> tileMapChanged = [this](Resource& resource)->bool {
			reloadResource();
			return true;
		};

		Mesh* mesh = nullptr;
		Material* material = nullptr;
		SpriteInputs inputs;

		inline void uninitTileMapComponent() {
			safeRelease(mesh);
			safeRelease(material);
		};

		virtual CoroutineTask<void> onInit();

		virtual void onUninit() {
			uninitTileMapComponent();
		};

		void reloadResource();

	public:
		TileMapComponent(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {}

		~TileMapComponent() {
			if (IsInitialized)
				uninitTileMapComponent();
			if (tileMap)
				tileMap->release();
		}

		inline TileMap* getTileMap() {
			return tileMap;
		}

		inline void setTileMap(TileMap* tileMap) {
			if (this->tileMap)
				this->tileMap->validChanged -= tileMapChanged;
			setPointer(this->tileMap, tileMap);
			if (tileMap)
				tileMap->validChanged += tileMapChanged;
			if (material && tileMap)
				inputs.ColorTexture = tileMap->TileSet->TextureAtlas->get();
		}

		__declspec(property(get = getTileMap, put = setTileMap)) TileMap* TileMap;

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
			if (material) {
				inputs.init(material->Inputs);
				if (tileMap)
					inputs.ColorTexture = tileMap->TileSet->TextureAtlas->get();
			}
		}

		__declspec(property(put = setMaterial)) Material* Material;

		virtual void draw(RenderGroup& group) override;
	};
}
