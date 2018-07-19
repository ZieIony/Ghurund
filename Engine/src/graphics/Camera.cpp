#include "Camera.h"

namespace Ghurund {
    const Array<ResourceFormat> Camera::formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};

    void Camera::rebuild() {
        XMMATRIX view2, proj2;
        view2 = XMMatrixLookAtLH(XMLoadFloat3(&Position), XMLoadFloat3(&target.Position), XMLoadFloat3(&up));
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
        Position = XMFLOAT3(0, 0, 0);
        up = XMFLOAT3(0, 1, 0);
        target.Position = XMFLOAT3(0, 0, 1);
        dir = XMFLOAT3(0, 0, 1);
        right = XMFLOAT3(1, 0, 0);
        rebuild();

        Name = _T("camera");

        subentities.add(&target);
    }

    void Camera::initParameters(ParameterManager &parameterManager) {
        Entity::initParameters(parameterManager);
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

    void Camera::calcMouseRay(XMFLOAT3 *rayPos, XMFLOAT3 *rayDir, int x, int y)const {
        rayPos; rayDir; x; y;
        /*XMFLOAT3 pos2=XMFLOAT3((((float)x*2.0f)/(float)screenSize.x-1.0f),
        -(((float)y*2.0f)/(float)screenSize.y-1.0f),
        1);

        if(pers){	//rzut ortogonalny le?y
        pos2.x/=proj._11;
        pos2.y/=proj._22;
        }
        XMFLOAT4X4 m;
        MatrixInverse( &m, null, &view );

        // Transform the screen space pick ray into 3D space
        rayDir->x  = pos2.x*m._11 + pos2.y*m._21 + pos2.z*m._31;
        rayDir->y  = pos2.x*m._12 + pos2.y*m._22 + pos2.z*m._32;
        rayDir->z  = pos2.x*m._13 + pos2.y*m._23 + pos2.z*m._33;
        D3DXVec3Normalize(rayDir,rayDir);
        rayPos->x = m._41;
        rayPos->y = m._42;
        rayPos->z = m._43;

        // calc origin as intersection with near frustum

        *rayPos+=*rayDir*zNear;
        / *
        XMFLOAT3 target2=XMFLOAT3(pos2.x,pos2.y,1);
        XMFLOAT4X4 viewProjInv=view*proj;
        MatrixInverse(&viewProjInv,0,&viewProjInv);

        Vector4 pos4,target4;
        D3DXVec3Transform(&pos4, &pos2, &viewProjInv);
        D3DXVec3Transform(&target4, &target2, &viewProjInv);

        pos4/=pos4.z;
        target4/=target4.z;

        *rayPos=XMFLOAT3(pos4.x,pos4.y,pos4.z);
        *rayDir=XMFLOAT3(target4.x,target4.y,target4.z);
        * /
        */
    }

    void Camera::setPositionTargetUp(XMFLOAT3 & pos, XMFLOAT3 & target, XMFLOAT3 & up) {
        Position = pos;
        this->target.Position = target;

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
        /*Position = pos;

        XMVECTOR dv = XMLoadFloat3(&dir);
        XMStoreFloat3(&target, XMLoadFloat3(&pos)+dv);

        XMStoreFloat(&dist, XMVector3Length(dv));
        XMVECTOR uv = XMLoadFloat3(&up);
        XMStoreFloat3(&dir, XMVector3Normalize(dv));
        XMVECTOR rv = XMVector3Normalize(XMVector3Cross(dv, uv));
        XMStoreFloat3(&right, rv);
        uv = XMVector3Normalize(XMVector3Cross(rv, dv));
        XMStoreFloat3(&this->up, uv);*/
    }

    void Camera::setViewYawPitchRoll(float yaw, float pitch, float roll) {
        /*XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist==0?-1:-dist, 0);
        dv = XMVector3Transform(dv, rotation);
        XMStoreFloat3(&target, XMLoadFloat3(&Position)+dv);
        XMStoreFloat3(&dir, XMVector4Normalize(dv));
        XMStoreFloat3(&up, XMVector3Transform(XMVectorSet(0, 1, 0, 0), rotation));
        XMStoreFloat3(&right, XMVector3Transform(XMVectorSet(1, 0, 0, 0), rotation));*/
    }

    void Camera::setOrbitYawPitchRoll(float yaw, float pitch, float roll) {
        /*XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        XMVECTOR dv = XMVectorSet(0, 0, dist==0 ? -1 : -dist, 0);
        dv = XMVector3Transform(dv, rotation);
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&target)-dv);
        Position = pos;
        XMStoreFloat3(&dir, XMVector4Normalize(dv));
        XMStoreFloat3(&up, XMVector3Transform(XMVectorSet(0, 1, 0, 0), rotation));
        XMStoreFloat3(&right, XMVector3Transform(XMVectorSet(1, 0, 0, 0), rotation));*/
    }

    Status Camera::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
        MemoryInputStream stream(data);
        //memcpy(&position, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&target, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&right, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&dir, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&view, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&proj, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&viewProj, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&facing, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&screenSize, stream.readBytes(sizeof(XMFLOAT2)), sizeof(XMFLOAT2));
        fov = stream.readFloat();
        zNear = stream.readFloat();
        zFar = stream.readFloat();
        memcpy(&up, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        pers = stream.readBoolean();
        return Status::OK;
    }

    Status Camera::saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size) const {
        MemoryOutputStream stream(data);
        //stream.writeBytes((void*)&position, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&target, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&right, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&dir, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&view, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&proj, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&viewProj, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&facing, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&screenSize, sizeof(XMFLOAT2));
        stream.writeFloat(fov);
        stream.writeFloat(zNear);
        stream.writeFloat(zFar);
        stream.writeBytes((void*)&up, sizeof(XMFLOAT3));
        stream.writeFloat(pers);
        return Status::OK;
    }
}