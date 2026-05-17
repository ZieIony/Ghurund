#include "ghe3dpch.h"
#include "Camera3D.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/parameter/ParameterManager.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace ::DirectX;

	Camera3D::Camera3D():
		viewSize({ 640, 480 }),
		fov(XM_PI / 4),
		zNear(0.1f),
		zFar(10000.0f),
		pers(true),
		pos(XMFLOAT3(0, 0, 0)),
		up(XMFLOAT3(0, 1, 0)),
		target(XMFLOAT3(0, 0, 1)),
		dir(XMFLOAT3(0, 0, 1)),
		right(XMFLOAT3(1, 0, 0)),
		dist(1.0f) {

		float rotation = 0.0f;
		//setPositionTargetUp(XMFLOAT3(sin(rotation) * 600, 200, cos(rotation) * 600), XMFLOAT3(0, 50, 0), XMFLOAT3(0, 1, 0));

		parameterDirection = ghnew Float3Parameter(CAMERA_DIRECTION);
		parameterPosition = ghnew Float3Parameter(CAMERA_POSITION);
		parameterTarget = ghnew Float3Parameter(CAMERA_TARGET);
		parameterUp = ghnew Float3Parameter(CAMERA_UP);
		parameterRight = ghnew Float3Parameter(CAMERA_RIGHT);

		parameterFov = ghnew FloatParameter(FOV);
		parameterZNear = ghnew FloatParameter(ZNEAR);
		parameterZFar = ghnew FloatParameter(ZFAR);

		parameterView = ghnew MatrixParameter(VIEW);
		parameterProjection = ghnew MatrixParameter(PROJECTION);
		parameterViewProjection = ghnew MatrixParameter(VIEW_PROJECTION);
		parameterViewProjectionInv = ghnew MatrixParameter(VIEW_PROJECTION_INV);
	}

	Camera3D::~Camera3D() {
		parameterDirection->release();
		parameterPosition->release();
		parameterTarget->release();
		parameterUp->release();
		parameterRight->release();

		parameterFov->release();
		parameterZNear->release();
		parameterZFar->release();

		parameterView->release();
		parameterProjection->release();
		parameterViewProjection->release();
		parameterViewProjectionInv->release();
	}

	void Camera3D::update() {
		XMMATRIX viewTemp, projTemp, viewProjTemp, viewProjInvTemp;
		XMFLOAT4X4 viewTransposed, projTransposed, viewProjTransposed, viewProjInvTransposed;
	
		viewTemp = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&target), XMLoadFloat3(&up));
		XMStoreFloat4x4(&view, XMMatrixTranspose(viewTemp));
		if (pers) {
			projTemp = XMMatrixPerspectiveFovLH(fov, getAspect(), zNear, zFar);
		} else {
			projTemp = XMMatrixOrthographicLH((float)viewSize.Width, (float)viewSize.Height, zNear, zFar);
		}
		XMStoreFloat4x4(&proj, projTemp);
	
		viewProjTemp = viewTemp * projTemp;
		XMStoreFloat4x4(&viewProj, viewProjTemp);
		viewProjInvTemp = XMMatrixInverse(nullptr, viewProjTemp);
		XMStoreFloat4x4(&viewProjInv, viewProjInvTemp);

		parameterDirection->Value = dir;
		parameterPosition->Value = pos;
		parameterUp->Value = up;
		parameterRight->Value = right;
		parameterFov->Value = fov;
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

	void Camera3D::apply(ParameterManager& parameterManager) {
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

	void Camera3D::calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir)const {
		XMFLOAT3 v = { (float)mousePos.x, (float)mousePos.y, 0 };
		XMVECTOR rayPos2 = XMVector3Unproject(XMLoadFloat3(&v),
			0, 0, (float)viewSize.Width, (float)viewSize.Height, 0, 1,
			XMLoadFloat4x4(&proj),
			XMLoadFloat4x4(&view),
			XMMatrixIdentity());

		XMFLOAT3 v2 = { (float)mousePos.x, (float)mousePos.y, 1 };
		XMVECTOR rayTarget2 = XMVector3Unproject(XMLoadFloat3(&v2),
			0, 0, (float)viewSize.Width, (float)viewSize.Height, 0, 1,
			XMLoadFloat4x4(&proj),
			XMLoadFloat4x4(&view),
			XMMatrixIdentity());

		XMStoreFloat3(&rayPos, rayPos2);
		XMStoreFloat3(&rayDir, XMVector3Normalize(rayTarget2 - rayPos2));
	}

	void Camera3D::setPositionTargetUp(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up) {
		this->pos = pos;
		this->target = target;

		XMVECTOR dv = XMLoadFloat3(&target) - XMLoadFloat3(&pos);

		XMStoreFloat(&dist, XMVector3Length(dv));
		XMVECTOR uv = XMLoadFloat3(&up);
		XMStoreFloat3(&dir, XMVector3Normalize(dv));
		XMVECTOR rv = XMVector3Normalize(XMVector3Cross(uv, dv));
		XMStoreFloat3(&right, rv);
		XMStoreFloat3(&this->up, XMVector3Normalize(uv));
	}

	void Camera3D::setPositionDirectionDistanceUp(const XMFLOAT3& pos, const XMFLOAT3& dir, float dist, const XMFLOAT3& up) {
		this->pos = pos;
		XMVECTOR dv = XMVector3Normalize(XMLoadFloat3(&dir));
		XMStoreFloat3(&target, XMLoadFloat3(&pos) + dv * dist);

		this->dist = dist;
		XMVECTOR uv = XMLoadFloat3(&up);
		XMStoreFloat3(&this->dir, dv);
		XMVECTOR rv = XMVector3Normalize(XMVector3Cross(uv, dv));
		XMStoreFloat3(&right, rv);
		XMStoreFloat3(&this->up, XMVector3Normalize(uv));
	}

	void Camera3D::setRotation(float yaw, float pitch, float roll) {
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
		dv = XMVector3TransformNormal(dv, rotation);
		XMStoreFloat3(&target, XMLoadFloat3(&pos) + dv);
		setPositionTargetUp(pos, target, up);
	}

	void Camera3D::setOrbit(float yaw, float pitch, float roll) {
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
		dv = XMVector3TransformNormal(dv, rotation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMLoadFloat3(&target) - dv);
		setPositionTargetUp(pos, target, up);
	}

	void Camera3D::rotate(float yaw, float pitch, float roll) {
		XMFLOAT3 rotation = getRotation();

		setRotation(rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
	}

	void Camera3D::orbit(float yaw, float pitch, float roll) {
		XMFLOAT3 rotation = getRotation();

		setOrbit(rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
	}

	void Camera3D::pan(float x, float y) {
		XMVECTOR rv = XMLoadFloat3(&right);
		XMVECTOR uv = XMLoadFloat3(&up);
		XMStoreFloat3(&target, XMLoadFloat3(&target) + rv * x + uv * y);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMLoadFloat3(&pos) + rv * x + uv * y);
		this->pos = pos;
	}

	void Camera3D::zoom(float z) {
		XMVECTOR dv = XMLoadFloat3(&dir);
		XMVECTOR pv = XMLoadFloat3(&pos);
		XMVECTOR pv2 = pv + dv * z;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, pv2);
		this->pos = pos;
		XMStoreFloat(&dist, XMVector3Length(XMLoadFloat3(&target) - pv2));
	}

	/*void Camera::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
		//__super::loadInternal(context, workingDir, stream, options);

		memcpy(&pos, stream.readBytes(sizeof(pos)), sizeof(pos));
		memcpy(&target, stream.readBytes(sizeof(target)), sizeof(target));
		memcpy(&right, stream.readBytes(sizeof(right)), sizeof(right));
		memcpy(&dir, stream.readBytes(sizeof(dir)), sizeof(dir));
		memcpy(&view, stream.readBytes(sizeof(view)), sizeof(view));
		memcpy(&proj, stream.readBytes(sizeof(proj)), sizeof(proj));
		memcpy(&viewProj, stream.readBytes(sizeof(viewProj)), sizeof(viewProj));
		//memcpy(&facing, stream.readBytes(sizeof(facing)), sizeof(facing));
		memcpy(&viewSize, stream.readBytes(sizeof(viewSize)), sizeof(viewSize));
		fov = stream.readFloat();
		zNear = stream.readFloat();
		zFar = stream.readFloat();
		memcpy(&up, stream.readBytes(sizeof(up)), sizeof(up));
		pers = stream.readBoolean();
	}

	void Camera::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		//__super::saveInternal(context, workingDir, stream, options);

		stream.writeBytes(&pos, sizeof(pos));
		stream.writeBytes(&target, sizeof(target));
		stream.writeBytes(&right, sizeof(right));
		stream.writeBytes(&dir, sizeof(dir));
		stream.writeBytes(&view, sizeof(view));
		stream.writeBytes(&proj, sizeof(proj));
		stream.writeBytes(&viewProj, sizeof(viewProj));
		//stream.writeBytes(&facing, sizeof(facing));
		stream.writeBytes(&viewSize, sizeof(viewSize));
		stream.writeFloat(fov);
		stream.writeFloat(zNear);
		stream.writeFloat(zFar);
		stream.writeBytes(&up, sizeof(up));
		stream.writeBoolean(pers);
	}*/

	const Ghurund::Core::Type& Camera3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Camera3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}