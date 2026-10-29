#include "ghe2dpch.h"
#include "VisualizationComponent2D.h"

#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	VisualizationComponent2D::~VisualizationComponent2D() {
		if (mesh)
			mesh->release();
		if (material)
			material->release();
	}

	CoroutineTask<void> VisualizationComponent2D::init(ResourceManager& resourceManager, const RigidBodyComponent2D& rigidBody) {
		auto visMesh = co_await resourceManager.load<Ghurund::Engine::Mesh>(Graphics2DFeature::MESH_SPRITE);
		Mesh = visMesh.get();
		if (rigidBody.ShapeType == ShapeType::BOX) {
			auto visMaterial = co_await resourceManager.load<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_VISUALIZATION_BOX);
			Material = visMaterial.get();
		} else if (rigidBody.ShapeType == ShapeType::CAPSULE) {
			auto visMaterial = co_await resourceManager.load<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_VISUALIZATION_CAPSULE);
			Material = visMaterial.get();
		} else if (rigidBody.ShapeType == ShapeType::SEGMENT) {
			auto visMaterial = co_await resourceManager.load<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_VISUALIZATION_SEGMENT);
			Material = visMaterial.get();
		}
	}

	void VisualizationComponent2D::update(const RigidBodyComponent2D& rigidBody) {
		XMFLOAT4X4 world;
		auto w = XMMatrixScaling(rigidBody.Size.Width, rigidBody.Size.Height, 1);
		if (rigidBody.BodyType == BodyType::STATIC) {
			auto rotation = XMMatrixRotationZ(rigidBody.Rotation / 180 * XM_PI);
			auto translation = XMMatrixTranslation(rigidBody.Position.x, rigidBody.Position.y, 0);
			w = w * rotation * translation;
		}
		XMStoreFloat4x4(&world, w);
		Transformation = world;
		extents = { rigidBody.Size.Width / 2, rigidBody.Size.Height / 2 };
	}
}
