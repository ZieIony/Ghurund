#include "ghepch.h"
#include "Camera.h"

#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/TypeBuilder.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace ::DirectX;

	void Camera::rebuild() {
		XMMATRIX view2, proj2, viewProj2;
		view2 = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&target), XMLoadFloat3(&up));
		XMStoreFloat4x4(&view, XMMatrixTranspose(view2));
		if (pers) {
			proj2 = XMMatrixPerspectiveFovLH(fov, getAspect(), zNear, zFar);
		} else {
			proj2 = XMMatrixOrthographicLH((float)viewSize.Width, (float)viewSize.Height, zNear, zFar);
		}
		XMStoreFloat4x4(&proj, XMMatrixTranspose(proj2));
		viewProj2 = view2 * proj2;
		XMStoreFloat4x4(&viewProj, XMMatrixTranspose(viewProj2));
		XMStoreFloat4x4(&viewProjInv, XMMatrixTranspose(XMMatrixInverse(nullptr, viewProj2)));

		parameterDirection->Value = dir;
		parameterPosition->Value = pos;
		parameterUp->Value = up;
		parameterRight->Value = right;
		parameterFov->Value = fov;
		parameterZNear->Value = zNear;
		parameterZFar->Value = zFar;
		parameterView->Value = view;
		parameterProjection->Value = proj;
		parameterViewProjection->Value = viewProj;
		parameterViewProjectionInv->Value = viewProjInv;
	}

	Camera::Camera():
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

		parameters.put(parameterDirection = ghnew Float3Parameter(CAMERA_DIRECTION));
		parameters.put(parameterPosition = ghnew Float3Parameter(CAMERA_POSITION));
		parameters.put(parameterTarget = ghnew Float3Parameter(CAMERA_TARGET));
		parameters.put(parameterUp = ghnew Float3Parameter(CAMERA_UP));
		parameters.put(parameterRight = ghnew Float3Parameter(CAMERA_RIGHT));

		parameters.put(parameterFov = ghnew FloatParameter(FOV));
		parameters.put(parameterZNear = ghnew FloatParameter(ZNEAR));
		parameters.put(parameterZFar = ghnew FloatParameter(ZFAR));

		parameters.put(parameterView = ghnew MatrixParameter(VIEW));
		parameters.put(parameterProjection = ghnew MatrixParameter(PROJECTION));
		parameters.put(parameterViewProjection = ghnew MatrixParameter(VIEW_PROJECTION));
		parameters.put(parameterViewProjectionInv = ghnew MatrixParameter(VIEW_PROJECTION_INV));
	}

	Camera::~Camera() {
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

	void Camera::calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir)const {
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

	void Camera::setPositionTargetUp(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up) {
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

	void Camera::setPositionDirectionDistanceUp(const XMFLOAT3& pos, const XMFLOAT3& dir, float dist, const XMFLOAT3& up) {
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

	void Camera::setRotation(float yaw, float pitch, float roll) {
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
		dv = XMVector3TransformNormal(dv, rotation);
		XMStoreFloat3(&target, XMLoadFloat3(&pos) + dv);
		setPositionTargetUp(pos, target, up);
	}

	void Camera::setOrbit(float yaw, float pitch, float roll) {
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
		dv = XMVector3TransformNormal(dv, rotation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMLoadFloat3(&target) - dv);
		setPositionTargetUp(pos, target, up);
	}

	void Camera::rotate(float yaw, float pitch, float roll) {
		XMFLOAT3 rotation = getRotation();

		setRotation(rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
	}

	void Camera::orbit(float yaw, float pitch, float roll) {
		XMFLOAT3 rotation = getRotation();

		setOrbit(rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
	}

	void Camera::pan(float x, float y) {
		XMVECTOR rv = XMLoadFloat3(&right);
		XMVECTOR uv = XMLoadFloat3(&up);
		XMStoreFloat3(&target, XMLoadFloat3(&target) + rv * x + uv * y);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMLoadFloat3(&pos) + rv * x + uv * y);
		this->pos = pos;
	}

	void Camera::zoom(float z) {
		XMVECTOR dv = XMLoadFloat3(&dir);
		XMVECTOR pv = XMLoadFloat3(&pos);
		XMVECTOR pv2 = pv + dv * z;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, pv2);
		this->pos = pos;
		XMStoreFloat(&dist, XMVector3Length(XMLoadFloat3(&target) - pv2));
	}

	void Camera::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
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
	}

	const Ghurund::Core::Type& Camera::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Camera>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}