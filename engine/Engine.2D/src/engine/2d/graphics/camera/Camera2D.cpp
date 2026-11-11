#include "ghe2dpch.h"
#include "Camera2D.h"

#include "core/reflection/TypeBuilder.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	Camera2D::Camera2D():
		pos({ 0, 0, -100 }),
		up({ 0, 1, 0 }),
		right({ 1, 0, 0 }) {

		zNear = 100.0f;
		zFar = 200.0f;
		viewSize = { 640, 480 };
	}

	void Camera2D::update() {
		XMFLOAT3 dir = { 0, 0, 1 };
	
		XMMATRIX viewTemp = XMMatrixLookToLH(XMLoadFloat3(&pos), XMLoadFloat3(&dir), XMLoadFloat3(&up));
		XMStoreFloat4x4(&view, viewTemp);
		XMMATRIX projTemp = XMMatrixOrthographicLH((float)viewSize.Width, (float)viewSize.Height, zNear, zFar);
		XMStoreFloat4x4(&proj, projTemp);
	
		XMMATRIX viewProjTemp = viewTemp * projTemp;
		XMStoreFloat4x4(&viewProj, XMMatrixTranspose(viewProjTemp));
		XMMATRIX viewProjInvTemp = XMMatrixInverse(nullptr, viewProjTemp);
		XMStoreFloat4x4(&viewProjInv, XMMatrixTranspose(viewProjInvTemp));

		BoundingBox boundingBox;
		XMFLOAT3 leftTop = { -(viewSize.Width / 2.0f), -(viewSize.Height / 2.0f), zNear };
		XMFLOAT3 rightBottom = { viewSize.Width / 2.0f, viewSize.Height / 2.0f, zFar };
		BoundingBox::CreateFromPoints(boundingBox, XMLoadFloat3(&leftTop), XMLoadFloat3(&rightBottom));
		BoundingOrientedBox::CreateFromBoundingBox(boundingOrientedBox, boundingBox);
		auto viewInvTemp = XMMatrixInverse(nullptr, viewTemp);
		boundingOrientedBox.Transform(boundingOrientedBox, viewInvTemp);
	}

	void Camera2D::apply(GlobalParameters& globalParameters) {
		globalParameters.viewProj = viewProj;
		globalParameters.cameraPos = { pos.x, pos.y, 0 };
	}

	void Camera2D::setPositionUp(const XMFLOAT2& pos, const XMFLOAT2& up) {
		this->pos = { pos.x, pos.y, -zNear };

		XMFLOAT3 dir = { 0, 0, 1 };
		XMVECTOR dv = XMLoadFloat3(&dir);

		XMFLOAT3 u = { up.x, up.y, 0 };
		XMVECTOR uv = XMLoadFloat3(&u);
		XMStoreFloat3(&dir, XMVector3Normalize(dv));
		XMVECTOR rv = XMVector3Normalize(XMVector3Cross(uv, dv));
		XMStoreFloat3(&right, rv);
		XMStoreFloat3(&this->up, XMVector3Normalize(uv));
	}

	void Camera2D::setRoll(float rotation) {
		/*XMMATRIX r = XMMatrixRotationRollPitchYaw(0, 0, rotation);
		XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
		dv = XMVector3TransformNormal(dv, r);
		setPositionUp(pos, up);*/
	}

	void Camera2D::rotate(float delta) {
		//setRotation(getRotation() + delta);
	}

	void Camera2D::pan(float x, float y) {
		XMVECTOR rv = XMLoadFloat3(&right);
		XMVECTOR uv = XMLoadFloat3(&up);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMLoadFloat3(&pos) + rv * x + uv * y);
		this->pos = pos;
	}

	/*void Camera2D::load_internal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOptions options) {
		//__super::load_internal(context, workingDir, stream, options);

		memcpy(&pos, stream.readBytes(sizeof(pos)), sizeof(pos));
		memcpy(&right, stream.readBytes(sizeof(right)), sizeof(right));
		memcpy(&view, stream.readBytes(sizeof(view)), sizeof(view));
		memcpy(&proj, stream.readBytes(sizeof(proj)), sizeof(proj));
		memcpy(&viewProj, stream.readBytes(sizeof(viewProj)), sizeof(viewProj));
		memcpy(&viewSize, stream.readBytes(sizeof(viewSize)), sizeof(viewSize));
		zNear = stream.readFloat();
		zFar = stream.readFloat();
		memcpy(&up, stream.readBytes(sizeof(up)), sizeof(up));
	}

	void Camera2D::save_internal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOptions options) const {
		//__super::save_internal(context, workingDir, stream, options);

		stream.writeBytes(&pos, sizeof(pos));
		stream.writeBytes(&right, sizeof(right));
		stream.writeBytes(&view, sizeof(view));
		stream.writeBytes(&proj, sizeof(proj));
		stream.writeBytes(&viewProj, sizeof(viewProj));
		stream.writeBytes(&viewSize, sizeof(viewSize));
		stream.writeFloat(zNear);
		stream.writeFloat(zFar);
		stream.writeBytes(&up, sizeof(up));
	}*/

	const Ghurund::Core::Type& Camera2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Camera2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}