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

	void VisualizationComponent2D::init(uint32_t id, const RigidBodyComponent2D& rigidBody) {
		this->id = id;
		Mesh = Graphics2DFeature::MESH_SPRITE;
		if (rigidBody.ShapeType == ShapeType::BOX) {
			Material = Graphics2DFeature::MATERIAL_VISUALIZATION_BOX;
		} else if (rigidBody.ShapeType == ShapeType::CAPSULE) {
			Material = Graphics2DFeature::MATERIAL_VISUALIZATION_CAPSULE;
		} else if (rigidBody.ShapeType == ShapeType::SEGMENT) {
			Material = Graphics2DFeature::MATERIAL_VISUALIZATION_SEGMENT;
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
		worldTransformation = world;
		extents = { rigidBody.Size.Width / 2, rigidBody.Size.Height / 2 };
	}
}
