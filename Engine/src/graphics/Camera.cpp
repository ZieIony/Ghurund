#include "Camera.h"

namespace Ghurund {
    void Camera::rebuild() {
        XMMATRIX view2, proj2;
        view2 = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&target), XMLoadFloat3(&up));
        XMStoreFloat4x4(&view, view2);
        if(pers) {
            proj2 = XMMatrixPerspectiveFovLH(fov, getAspect(), zNear, zFar);
        } else {
            proj2 = XMMatrixOrthographicLH((float)screenSize.x, (float)screenSize.y, zNear, zFar);
        }
        XMStoreFloat4x4(&proj, proj2);
        XMStoreFloat4x4(&viewProj, view2*proj2);
    }

    Camera::Camera() {
        screenSize = XMFLOAT2(640, 480);
        fov = XM_PI/4;
        zNear = 0.1f;
        zFar = 10000.0f;
        pers = true;
        pos = XMFLOAT3(0, 0, 0);
        up = XMFLOAT3(0, 1, 0);
        target = XMFLOAT3(0, 0, 1);
        dir = XMFLOAT3(0, 0, 1);
        right = XMFLOAT3(1, 0, 0);
        rebuild();

        float rotation = 0.0f;
        setPositionTargetUp(XMFLOAT3(sin(rotation)*600, 200, cos(rotation)*600), XMFLOAT3(0, 50, 0), XMFLOAT3(0, 1, 0));

        Name = _T("camera");
    }

    void Camera::initParameters(ParameterManager &parameterManager) {
        parameterDirection = parameterManager.add(Parameter::DIRECTION, ParameterType::FLOAT3);
        parameters.add(parameterDirection);
        parameterUp = parameterManager.add(Parameter::UP, ParameterType::FLOAT3);
        parameters.add(parameterUp);
        parameterRight = parameterManager.add(Parameter::RIGHT, ParameterType::FLOAT3);
        parameters.add(parameterRight);
        parameterFov = parameterManager.add(Parameter::FOV, ParameterType::FLOAT);
        parameters.add(parameterFov);
        parameterZNear = parameterManager.add(Parameter::ZNEAR, ParameterType::FLOAT);
        parameters.add(parameterZNear);
        parameterZFar = parameterManager.add(Parameter::ZFAR, ParameterType::FLOAT);
        parameters.add(parameterZFar);
        parameterView = parameterManager.add(Parameter::VIEW, ParameterType::MATRIX);
        parameters.add(parameterView);
        parameterProjection = parameterManager.add(Parameter::PROJECTION, ParameterType::MATRIX);
        parameters.add(parameterProjection);
        parameterViewProjection = parameterManager.add(Parameter::VIEW_PROJECTION, ParameterType::MATRIX);
        parameters.add(parameterViewProjection);
    }

    void Camera::fillParameters() {
        rebuild();
        parameterDirection->setValue(&dir);
        parameterUp->setValue(&up);
        parameterRight->setValue(&right);
        parameterFov->setValue(&fov);
        parameterZNear->setValue(&zNear);
        parameterZFar->setValue(&zFar);
        parameterView->setValue(&view);
        parameterProjection->setValue(&proj);
        parameterViewProjection->setValue(&viewProj);
    }

    void Camera::calcMouseRay(XMINT2 &mousePos, XMFLOAT3 &rayPos, XMFLOAT3 &rayDir)const {
        XMVECTOR rayPos2 = XMVector3Unproject(XMLoadFloat3(&XMFLOAT3((float)mousePos.x, (float)mousePos.y, 0)),
                                              0, 0, screenSize.x, screenSize.y, 0, 1,
                                              XMLoadFloat4x4(&proj),
                                              XMLoadFloat4x4(&view),
                                              XMMatrixIdentity());

        XMVECTOR rayTarget2 = XMVector3Unproject(XMLoadFloat3(&XMFLOAT3((float)mousePos.x, (float)mousePos.y, 1)),
                                                 0, 0, screenSize.x, screenSize.y, 0, 1,
                                                 XMLoadFloat4x4(&proj),
                                                 XMLoadFloat4x4(&view),
                                                 XMMatrixIdentity());

        XMStoreFloat3(&rayPos, rayPos2);
        XMStoreFloat3(&rayDir, XMVector3Normalize(rayTarget2 - rayPos2));
    }

    void Camera::setPositionTargetUp(XMFLOAT3 & pos, XMFLOAT3 & target, XMFLOAT3 & up) {
        this->pos = pos;
        this->target = target;

        XMVECTOR dv = XMLoadFloat3(&target)-XMLoadFloat3(&pos);

        XMStoreFloat(&dist, XMVector3Length(dv));
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&dir, XMVector3Normalize(dv));
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(dv, uv));
        XMStoreFloat3(&right, rv);
        uv = XMVector3Normalize(XMVector3Cross(rv, dv));
        XMStoreFloat3(&this->up, uv);
    }

    void Camera::setPositionDirectionUp(XMFLOAT3 & pos, XMFLOAT3 & dir, XMFLOAT3 & up) {
        this->pos = pos;
        XMStoreFloat3(&target, XMLoadFloat3(&target)-XMLoadFloat3(&pos));

        XMVECTOR dv = XMLoadFloat3(&dir);

        XMStoreFloat(&dist, XMVector3Length(dv));
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&this->dir, XMVector3Normalize(dv));
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(dv, uv));
        XMStoreFloat3(&right, rv);
        uv = XMVector3Normalize(XMVector3Cross(rv, dv));
        XMStoreFloat3(&this->up, uv);
    }

    void Camera::setPositionDistanceRotation(XMFLOAT3 &pos, float dist, float yaw, float pitch, float roll) {
        this->pos = pos;
        this->dist = dist;
        setRotation(yaw, pitch, roll);
    }

    void Camera::setTargetDistanceOrbit(XMFLOAT3 &target, float dist, float yaw, float pitch, float roll) {
        this->target = target;
        this->dist = dist;
        setOrbit(yaw, pitch, roll);
    }

    void Camera::setRotation(float yaw, float pitch, float roll) {
        XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist==0 ? -1 : -dist, 0);
        dv = XMVector3Transform(dv, rotation);
        XMStoreFloat3(&target, XMLoadFloat3(&Position)+dv);
        XMStoreFloat3(&dir, XMVector4Normalize(dv));
        XMStoreFloat3(&up, XMVector3Transform(XMVectorSet(0, 1, 0, 0), rotation));
        XMStoreFloat3(&right, XMVector3Transform(XMVectorSet(1, 0, 0, 0), rotation));
    }

    void Camera::setOrbit(float yaw, float pitch, float roll) {
        XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist==0 ? -1 : -dist, 0);
        dv = XMVector3Transform(dv, rotation);
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&target)-dv);
        this->pos = pos;
        XMStoreFloat3(&dir, XMVector4Normalize(dv));
        XMStoreFloat3(&up, XMVector3Transform(XMVectorSet(0, 1, 0, 0), rotation));
        XMStoreFloat3(&right, XMVector3Transform(XMVectorSet(1, 0, 0, 0), rotation));
    }

    void Camera::rotate(float yaw, float pitch, float roll) {
        float currentYaw = atan2(dir.x, dir.z)+XM_PI;
        float currentPitch = atan2f(dir.y, sqrtf(dir.x*dir.x+dir.z*dir.z));
        float currentRoll = atan2f(right.y, 1);

        setRotation(currentYaw+yaw, currentPitch+pitch, currentRoll+roll);
    }

    void Camera::orbit(float yaw, float pitch, float roll) {
        float currentYaw = atan2f(dir.x, dir.z)+XM_PI;
        float currentPitch = atan2f(dir.y, sqrtf(dir.x*dir.x+dir.z*dir.z));
        float currentRoll = atan2f(right.y, 1);

        setOrbit(currentYaw+yaw, currentPitch+pitch, currentRoll+roll);
    }

    void Camera::pan(float x, float y) {
        XMVECTOR rv = XMLoadFloat3(&right);
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&target, XMLoadFloat3(&target)+rv*x+uv*y);
        XMStoreFloat3(&pos, XMLoadFloat3(&pos)+rv*x+uv*y);
    }

    void Camera::zoom(float z) {
        XMVECTOR dv = XMLoadFloat3(&dir);
        XMStoreFloat3(&target, XMLoadFloat3(&target)+dv*z);
        XMStoreFloat3(&pos, XMLoadFloat3(&pos)+dv*z);
    }

    Status Camera::loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
        memcpy(&pos, stream.readBytes(sizeof(pos)), sizeof(pos));
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

    Status Camera::saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
        stream.write<XMFLOAT3>(pos);
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
}