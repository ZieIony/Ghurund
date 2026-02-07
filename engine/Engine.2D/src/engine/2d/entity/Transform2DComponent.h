#pragma once

#include "engine/2d/entity/Component2D.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class Transform2DComponent:public ComponentGroup2D {
	private:
		XMFLOAT2 position = {}, scale = { 1,1 };
		float rotation = {};
		XMFLOAT4X4 localTransformation;

	protected:
		virtual void setPositionInternal(const XMFLOAT2& pos) override {
			this->position = pos;
		}

		virtual XMFLOAT2 getPositionInternal() const override {
			return position;
		}

	public:
		inline const XMFLOAT4X4& getTransformation() const {
			return localTransformation;
		}

		__declspec(property(get = getTransformation)) const XMFLOAT4X4& Transformation;

		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}

		void setRotation(float rotation) {
			this->rotation = rotation;
		}

		inline float getRotation() const {
			return rotation;
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		void setScale(const XMFLOAT2& scale) {
			this->scale = scale;
		}

		void setScale(float x, float y) {
			this->scale.x = x;
			this->scale.y = y;
		}

		inline const XMFLOAT2& getScale() const {
			return scale;
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT2& Scale;

		virtual void update(uint64_t time) override {
			auto scaling = XMMatrixScaling(Scale.x, Scale.y, 1);
			auto rotation = XMMatrixRotationZ(Rotation);
			auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
			auto w = scaling * rotation * translation;
			XMStoreFloat4x4(&localTransformation, w);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) override {
			auto w = XMLoadFloat4x4(&parentTransformation)* XMLoadFloat4x4(&localTransformation);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, w);
			__super::draw(group, world);
		}
	};
}