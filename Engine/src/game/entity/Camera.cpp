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

    Camera::Camera():parameters(Array<Parameter*>(9)) {
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
        if(parameterDirection!=nullptr)
            return;

        int i = 0;
        parameters[i++] = parameterDirection = parameterManager.add(Parameter::DIRECTION, ParameterType::FLOAT3);
        parameters[i++] = parameterUp = parameterManager.add(Parameter::UP, ParameterType::FLOAT3);
        parameters[i++] = parameterRight = parameterManager.add(Parameter::RIGHT, ParameterType::FLOAT3);
        parameters[i++] = parameterFov = parameterManager.add(Parameter::FOV, ParameterType::FLOAT);
        parameters[i++] = parameterZNear = parameterManager.add(Parameter::ZNEAR, ParameterType::FLOAT);
        parameters[i++] = parameterZFar = parameterManager.add(Parameter::ZFAR, ParameterType::FLOAT);
        parameters[i++] = parameterView = parameterManager.add(Parameter::VIEW, ParameterType::MATRIX);
        parameters[i++] = parameterProjection = parameterManager.add(Parameter::PROJECTION, ParameterType::MATRIX);
        parameters[i++] = parameterViewProjection = parameterManager.add(Parameter::VIEW_PROJECTION, ParameterType::MATRIX);
    }

    void Camera::updateParameters() {
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

    void Camera::calcMouseRay(const XMINT2 &mousePos, XMFLOAT3 &rayPos, XMFLOAT3 &rayDir)const {
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

    void Camera::setPositionTargetUp(const XMFLOAT3 & pos, const XMFLOAT3 & target, const XMFLOAT3 & up) {
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
        notifyObjectChanged();
    }

    void Camera::setPositionDirectionUp(const XMFLOAT3 & pos, const XMFLOAT3 & dir, const XMFLOAT3 & up) {
        this->pos = pos;
        XMVECTOR dv = XMLoadFloat3(&dir);
        XMStoreFloat3(&target, XMLoadFloat3(&pos)+dv);

        XMStoreFloat(&dist, XMVector3Length(dv));
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&this->dir, XMVector3Normalize(dv));
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(dv, uv));
        XMStoreFloat3(&right, rv);
        uv = XMVector3Normalize(XMVector3Cross(rv, dv));
        XMStoreFloat3(&this->up, uv);
        notifyObjectChanged();
    }

    void Camera::setPositionDistanceRotation(const XMFLOAT3 &pos, float dist, float yaw, float pitch, float roll) {
        this->pos = pos;
        this->dist = dist;
        setRotation(yaw, pitch, roll);
    }

    void Camera::setTargetDistanceOrbit(const XMFLOAT3 &target, float dist, float yaw, float pitch, float roll) {
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
        notifyObjectChanged();
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
        notifyObjectChanged();
    }

    void Camera::rotate(float yaw, float pitch, float roll) {
        XMFLOAT3 &rotation = getRotation();

        setRotation(rotation.x+yaw, rotation.y+pitch, rotation.z+roll);
    }

    void Camera::orbit(float yaw, float pitch, float roll) {
        XMFLOAT3 &rotation = getRotation();

        setOrbit(rotation.x+yaw, rotation.y+pitch, rotation.z+roll);
    }

    void Camera::pan(float x, float y) {
        XMVECTOR rv = XMLoadFloat3(&right);
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&target, XMLoadFloat3(&target)+rv*x+uv*y);
        XMStoreFloat3(&pos, XMLoadFloat3(&pos)+rv*x+uv*y);
        notifyObjectChanged();
    }

    void Camera::zoom(float z) {
        XMVECTOR dv = XMLoadFloat3(&dir);
        XMVECTOR pv = XMLoadFloat3(&pos);
        XMVECTOR pv2 = pv+dv*z;
        XMStoreFloat3(&pos, pv2);
        XMStoreFloat(&dist, XMVector3Length(XMLoadFloat3(&target)-pv2));
        notifyObjectChanged();
    }

    Status Camera::loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) {
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

    Status Camera::saveInternal(ResourceManager &resourceManager, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const {
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