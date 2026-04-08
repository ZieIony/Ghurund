#pragma once

#include "TileMap.h"

#include "engine/2d/scene/component/TransformComponent2D.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class TileMapComponent:public TransformComponent2D {
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
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		SpriteInputs inputs;

		inline void uninitTileMapComponent() {
			Components.clear();
			safeRelease(mesh);
			safeRelease(material);
		};

		virtual CoroutineTask<void> onInit();

		virtual void onUninit() {
			uninitTileMapComponent();
			__super::onUninit();
		};

	public:
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
			setPointer(this->tileMap, tileMap);
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

		virtual void draw(RenderGroup& group) override {
			if (mesh && material) {
				auto w = XMLoadFloat4x4(&worldTransformation);
				XMFLOAT4X4 world;
				XMStoreFloat4x4(&world, XMMatrixTranspose(w));

				inputs.Transformation = world;
				group.objects.add(DrawPacket(mesh, material, drawOrder));
			}

			__super::draw(group);
		}
	};
}
