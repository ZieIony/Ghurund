#pragma once

#include "engine/2d/entity/Component2D.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class Transform2DComponent:public ComponentGroup2D {
	private:
		XMFLOAT2 position = {}, scale = { 1,1 };
		float rotation = {};
		XMFLOAT4X4 world;

	protected:
		virtual void setPositionInternal(const XMFLOAT2& pos) override {
			this->position = pos;
		}

		virtual XMFLOAT2 getPositionInternal() const override {
			return position;
		}

	public:
		inline const XMFLOAT4X4& getTransformation() const {
			return world;
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
		}

		virtual void draw(RenderGroup& group, const XMFLOAT2& parentPosition) override {
			__super::draw(group, parentPosition + position);
		}
	};
}