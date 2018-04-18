#include "Camera.h"

namespace Ghurund {
    void Camera::rebuild() {
        XMVECTOR up2, dir2, right2;
        dir2 = XMVector3Normalize(XMLoadFloat3(&dir));
        up2 = XMVector3Normalize(XMLoadFloat3(&up));
        right2 = XMVector3Cross(up2, dir2);
        right2 = XMVector3Normalize(right2);
        //up2=XMVector3Cross(dir2,right2);
        //up2=XMVector3Normalize(up2);
        //XMStoreFloat3(&up,up2);
        //XMStoreFloat3(&dir,dir2);
        XMStoreFloat3(&right, right2);
        /*XMMATRIX view2, proj2;
        view2 = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&target), up2);
        XMStoreFloat4x4(&view, view2);
        if(pers) {
            proj2 = XMMatrixPerspectiveFovLH(fov, aspect, zNear, zFar);
        } else {
            proj2 = XMMatrixOrthographicLH((float)screenSize.x, (float)screenSize.y, zNear, zFar);
        }
        XMStoreFloat4x4(&proj, proj2);*/
    }

    Camera::Camera() {
        screenSize = float2(640, 480);
        aspect = 4.0f/3.0f;
        fov = XM_PI/4;
        zNear = 0.1f;
        zFar = 1000.0f;
        pers = true;
        Position = XMFLOAT3(0, 0, 0);
        up = XMFLOAT3(0, 1, 0);
        target.Position = XMFLOAT3(0, 0, 1);
        dir = XMFLOAT3(0, 0, 1);
        right = XMFLOAT3(1, 0, 0);
        rebuild();

        Name = _T("camera");

        target.Name = _T("target");
        subentities.add(&target);
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

    Status Camera::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags) {
        MemoryInputStream stream(data);
        //memcpy(&position, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&target, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&right, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&dir, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        memcpy(&view, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&proj, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&facing, stream.readBytes(sizeof(XMFLOAT4X4)), sizeof(XMFLOAT4X4));
        memcpy(&screenSize, stream.readBytes(sizeof(float2)), sizeof(float2));
        aspect = stream.readFloat();
        fov = stream.readFloat();
        zNear = stream.readFloat();
        zFar = stream.readFloat();
        memcpy(&up, stream.readBytes(sizeof(XMFLOAT3)), sizeof(XMFLOAT3));
        pers = stream.readBoolean();
        return Status::OK;
    }

    Status Camera::saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags) const {
        MemoryOutputStream stream(data);
        //stream.writeBytes((void*)&position, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&target, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&right, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&dir, sizeof(XMFLOAT3));
        stream.writeBytes((void*)&view, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&proj, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&facing, sizeof(XMFLOAT4X4));
        stream.writeBytes((void*)&screenSize, sizeof(float2));
        stream.writeFloat(aspect);
        stream.writeFloat(fov);
        stream.writeFloat(zNear);
        stream.writeFloat(zFar);
        stream.writeBytes((void*)&up, sizeof(XMFLOAT3));
        stream.writeFloat(pers);
        return Status::OK;
    }
}