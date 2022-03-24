#include "Camera.h"

#include "core/io/File.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
    void Camera::rebuild(TransformComponent& transformComponent) {
        XMMATRIX view2, proj2, viewProj2;
        XMFLOAT3 pos = transformComponent.Position;
        view2 = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&target), XMLoadFloat3(&up));
        XMStoreFloat4x4(&view, view2);
        if (pers) {
            proj2 = XMMatrixPerspectiveFovLH(fov, getAspect(), zNear, zFar);
        } else {
            proj2 = XMMatrixOrthographicLH((float)screenSize.x, (float)screenSize.y, zNear, zFar);
        }
        XMStoreFloat4x4(&proj, proj2);
        viewProj2 = view2 * proj2;
        XMStoreFloat4x4(&viewProj, viewProj2);
        XMStoreFloat4x4(&viewProjInv, XMMatrixInverse(nullptr, viewProj2));
    }

    Camera::Camera():parameters(PointerArray<Parameter*>(11)) {
        screenSize = { 640, 480 };
        fov = XM_PI / 4;
        zNear = 0.1f;
        zFar = 10000.0f;
        pers = true;
        up = XMFLOAT3(0, 1, 0);
        target = XMFLOAT3(0, 0, 1);
        dir = XMFLOAT3(0, 0, 1);
        right = XMFLOAT3(1, 0, 0);
        //rebuild();

        float rotation = 0.0f;
        //setPositionTargetUp(XMFLOAT3(sin(rotation) * 600, 200, cos(rotation) * 600), XMFLOAT3(0, 50, 0), XMFLOAT3(0, 1, 0));
    }

    void Camera::initParameters(ParameterManager& parameterManager) {
        if (parameterDirection != nullptr)
            return;

        int i = 0;
        parameters.set(i++, parameterDirection = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::CAMERA_DIRECTION.Value]);
        parameters.set(i++, parameterPosition = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::CAMERA_POSITION.Value]);
        parameters.set(i++, parameterUp = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::CAMERA_UP.Value]);
        parameters.set(i++, parameterRight = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::CAMERA_RIGHT.Value]);

        parameters.set(i++, parameterFov = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::FOV.Value]);
        parameters.set(i++, parameterZNear = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::ZNEAR.Value]);
        parameters.set(i++, parameterZFar = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::ZFAR.Value]);

        parameters.set(i++, parameterView = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEW.Value]);
        parameters.set(i++, parameterProjection = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::PROJECTION.Value]);
        parameters.set(i++, parameterViewProjection = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEW_PROJECTION.Value]);
        parameters.set(i++, parameterViewProjectionInv = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEW_PROJECTION_INV.Value]);
    }

    void Camera::updateParameters() {
        //rebuild();
        parameterDirection->setValue(&dir);
        //parameterPosition->setValue(&transformComponent->Position);
        parameterUp->setValue(&up);
        parameterRight->setValue(&right);
        parameterFov->setValue(&fov);
        parameterZNear->setValue(&zNear);
        parameterZFar->setValue(&zFar);
        parameterView->setValue(&view);
        parameterProjection->setValue(&proj);
        parameterViewProjection->setValue(&viewProj);
        parameterViewProjectionInv->setValue(&viewProjInv);
    }

    void Camera::calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir)const {
        XMFLOAT3 v = { (float)mousePos.x, (float)mousePos.y, 0 };
        XMVECTOR rayPos2 = XMVector3Unproject(XMLoadFloat3(&v),
            0, 0, (float)screenSize.x, (float)screenSize.y, 0, 1,
            XMLoadFloat4x4(&proj),
            XMLoadFloat4x4(&view),
            XMMatrixIdentity());

        XMFLOAT3 v2 = { (float)mousePos.x, (float)mousePos.y, 1 };
        XMVECTOR rayTarget2 = XMVector3Unproject(XMLoadFloat3(&v2),
            0, 0, (float)screenSize.x, (float)screenSize.y, 0, 1,
            XMLoadFloat4x4(&proj),
            XMLoadFloat4x4(&view),
            XMMatrixIdentity());

        XMStoreFloat3(&rayPos, rayPos2);
        XMStoreFloat3(&rayDir, XMVector3Normalize(rayTarget2 - rayPos2));
    }

    void Camera::setPositionTargetUp(TransformComponent& transformComponent, const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up) {
        transformComponent.Position = pos;
        this->target = target;

        XMVECTOR dv = XMLoadFloat3(&target) - XMLoadFloat3(&pos);

        XMStoreFloat(&dist, XMVector3Length(dv));
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&dir, XMVector3Normalize(dv));
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(uv, dv));
        XMStoreFloat3(&right, rv);
        XMStoreFloat3(&this->up, XMVector3Normalize(uv));
    }

    void Camera::setPositionDirectionDistanceUp(TransformComponent& transformComponent, const XMFLOAT3& pos, const XMFLOAT3& dir, float dist, const XMFLOAT3& up) {
        transformComponent.Position = pos;
        XMVECTOR dv = XMVector3Normalize(XMLoadFloat3(&dir));
        XMStoreFloat3(&target, XMLoadFloat3(&pos) + dv * dist);

        this->dist = dist;
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&this->dir, dv);
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(uv, dv));
        XMStoreFloat3(&right, rv);
        XMStoreFloat3(&this->up, XMVector3Normalize(uv));
    }

    void Camera::setRotation(TransformComponent& transformComponent, float yaw, float pitch, float roll) {
        XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
        dv = XMVector3TransformNormal(dv, rotation);
        XMStoreFloat3(&target, XMLoadFloat3(&transformComponent.Position) + dv);
        setPositionTargetUp(transformComponent, transformComponent.Position, target, up);
    }

    void Camera::setOrbit(TransformComponent& transformComponent, float yaw, float pitch, float roll) {
        XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist == 0 ? -1 : -dist, 0);
        dv = XMVector3TransformNormal(dv, rotation);
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&target) - dv);
        setPositionTargetUp(transformComponent, pos, target, up);
    }

    void Camera::rotate(TransformComponent& transformComponent, float yaw, float pitch, float roll) {
        XMFLOAT3 rotation = getRotation();

        setRotation(transformComponent, rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
    }

    void Camera::orbit(TransformComponent& transformComponent, float yaw, float pitch, float roll) {
        XMFLOAT3 rotation = getRotation();

        setOrbit(transformComponent, rotation.x + yaw, rotation.y + pitch, rotation.z + roll);
    }

    void Camera::pan(TransformComponent& transformComponent, float x, float y) {
        XMVECTOR rv = XMLoadFloat3(&right);
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&target, XMLoadFloat3(&target) + rv * x + uv * y);
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&transformComponent.Position) + rv * x + uv * y);
        transformComponent.Position = pos;
    }

    void Camera::zoom(TransformComponent& transformComponent, float z) {
        XMVECTOR dv = XMLoadFloat3(&dir);
        XMVECTOR pv = XMLoadFloat3(&transformComponent.Position);
        XMVECTOR pv2 = pv + dv * z;
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, pv2);
        transformComponent.Position = pos;
        XMStoreFloat(&dist, XMVector3Length(XMLoadFloat3(&target) - pv2));
    }

    Status Camera::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        //__super::loadInternal(context, workingDir, stream, options);

        memcpy(&target, stream.readBytes(sizeof(target)), sizeof(target));
        memcpy(&right, stream.readBytes(sizeof(right)), sizeof(right));
        memcpy(&dir, stream.readBytes(sizeof(dir)), sizeof(dir));
        memcpy(&view, stream.readBytes(sizeof(view)), sizeof(view));
        memcpy(&proj, stream.readBytes(sizeof(proj)), sizeof(proj));
        memcpy(&viewProj, stream.readBytes(sizeof(viewProj)), sizeof(viewProj));
        memcpy(&facing, stream.readBytes(sizeof(facing)), sizeof(facing));
        memcpy(&screenSize, stream.readBytes(sizeof(screenSize)), sizeof(screenSize));
        fov = stream.readFloat();
        zNear = stream.readFloat();
        zFar = stream.readFloat();
        memcpy(&up, stream.readBytes(sizeof(up)), sizeof(up));
        pers = stream.readBoolean();

        return Status::OK;
    }

    Status Camera::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        //__super::saveInternal(context, workingDir, stream, options);

        stream.writeBytes(&target, sizeof(target));
        stream.writeBytes(&right, sizeof(right));
        stream.writeBytes(&dir, sizeof(dir));
        stream.writeBytes(&view, sizeof(view));
        stream.writeBytes(&proj, sizeof(proj));
        stream.writeBytes(&viewProj, sizeof(viewProj));
        stream.writeBytes(&facing, sizeof(facing));
        stream.writeBytes(&screenSize, sizeof(screenSize));
        stream.writeFloat(fov);
        stream.writeFloat(zNear);
        stream.writeFloat(zFar);
        stream.writeBytes(&up, sizeof(up));
        stream.writeBoolean(pers);

        return Status::OK;
    }

    const Ghurund::Core::Type& Camera::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Camera>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Camera>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Camera))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}