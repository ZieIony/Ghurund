#include "ghe2dpch.h"
#include "Camera2D.h"

#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/TypeBuilder.h"
#include "engine/parameter/ParameterManager.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	Camera2D::Camera2D():
		viewSize({ 640, 480 }),
		zNear(100.0f),
		zFar(200.0f),
		pos({ 0, 0, -100 }),
		up({ 0, 1, 0 }),
		right({ 1, 0, 0 }) {

		parameterPosition = ghnew Float3Parameter(CAMERA_POSITION);
		parameterUp = ghnew Float3Parameter(CAMERA_UP);
		parameterRight = ghnew Float3Parameter(CAMERA_RIGHT);

		parameterZNear = ghnew FloatParameter(ZNEAR);
		parameterZFar = ghnew FloatParameter(ZFAR);

		parameterView = ghnew MatrixParameter(VIEW);
		parameterProjection = ghnew MatrixParameter(PROJECTION);
		parameterViewProjection = ghnew MatrixParameter(VIEW_PROJECTION);
		parameterViewProjectionInv = ghnew MatrixParameter(VIEW_PROJECTION_INV);
	}

	Camera2D::~Camera2D() {
		parameterPosition->release();
		parameterUp->release();
		parameterRight->release();

		parameterZNear->release();
		parameterZFar->release();

		parameterView->release();
		parameterProjection->release();
		parameterViewProjection->release();
		parameterViewProjectionInv->release();
	}

	void Camera2D::update() {
		XMMATRIX viewTemp, projTemp, viewProjTemp, viewProjInvTemp;
		XMFLOAT4X4 viewTransposed, projTransposed, viewProjTransposed, viewProjInvTransposed;
		XMFLOAT3 dir = { 0, 0, 1 };
		viewTemp = XMMatrixLookToLH(XMLoadFloat3(&pos), XMLoadFloat3(&dir), XMLoadFloat3(&up));
		XMStoreFloat4x4(&view, viewTemp);
		projTemp = XMMatrixOrthographicLH((float)viewSize.Width, (float)viewSize.Height, zNear, zFar);
		XMStoreFloat4x4(&proj, projTemp);
		viewProjTemp = viewTemp * projTemp;
		XMStoreFloat4x4(&viewProj, viewProjTemp);
		viewProjInvTemp = XMMatrixInverse(nullptr, viewProjTemp);
		XMStoreFloat4x4(&viewProjInv, viewProjInvTemp);

		parameterPosition->Value = pos;
		parameterUp->Value = up;
		parameterRight->Value = right;
		parameterZNear->Value = zNear;
		parameterZFar->Value = zFar;

		XMStoreFloat4x4(&viewTransposed, XMMatrixTranspose(viewTemp));
		parameterView->Value = viewTransposed;
		XMStoreFloat4x4(&projTransposed, XMMatrixTranspose(projTemp));
		parameterProjection->Value = projTransposed;
		XMStoreFloat4x4(&viewProjTransposed, XMMatrixTranspose(viewProjTemp));
		parameterViewProjection->Value = viewProjTransposed;
		XMStoreFloat4x4(&viewProjInvTransposed, XMMatrixTranspose(viewProjInvTemp));
		parameterViewProjectionInv->Value = viewProjInvTransposed;
	}

	void Camera2D::apply(ParameterManager& parameterManager) {
		parameterManager.Parameters.put(parameterPosition);
		parameterManager.Parameters.put(parameterUp);
		parameterManager.Parameters.put(parameterRight);

		parameterManager.Parameters.put(parameterZNear);
		parameterManager.Parameters.put(parameterZFar);

		parameterManager.Parameters.put(parameterView);
		parameterManager.Parameters.put(parameterProjection);
		parameterManager.Parameters.put(parameterViewProjection);
		parameterManager.Parameters.put(parameterViewProjectionInv);
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

	void Camera2D::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
		//__super::loadInternal(context, workingDir, stream, options);

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

	void Camera2D::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		//__super::saveInternal(context, workingDir, stream, options);

		stream.writeBytes(&pos, sizeof(pos));
		stream.writeBytes(&right, sizeof(right));
		stream.writeBytes(&view, sizeof(view));
		stream.writeBytes(&proj, sizeof(proj));
		stream.writeBytes(&viewProj, sizeof(viewProj));
		stream.writeBytes(&viewSize, sizeof(viewSize));
		stream.writeFloat(zNear);
		stream.writeFloat(zFar);
		stream.writeBytes(&up, sizeof(up));
	}

	const Ghurund::Core::Type& Camera2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Camera2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}