#pragma once

#include "Graphics.h"
#include "core/MemoryStream.h"
#include "resource/Resource.h"
#include "game/ParameterProvider.h"
#include "game/Parameter.h"
#include "game/Entity.h"

namespace Ghurund {

    class Camera: public Entity {
    private:
        Entity target;
        XMFLOAT3 dir, right, up;
        XMFLOAT4X4 view, proj, facing;
        float2 screenSize;
        float aspect, fov, zNear, zFar, dist;
        bool pers;

        Parameter *parameterDirection,*parameterTarget;
        Parameter *parameterUp,*parameterRight;
        Parameter *parameterFov;
        Parameter *parameterZNear,*parameterZFar;
        Parameter *parameterView,*parameterProjection;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const;

        virtual void clean() {}

    public:

        Camera();

        virtual void initParameters(ParameterManager &parameterManager) {
            parameterDirection = parameterManager.add(Name+Parameter::DIRECTION, sizeof(dir));
            parameterTarget = parameterManager.add(Name+Parameter::TARGET, sizeof(target));
            parameterUp = parameterManager.add(Name+Parameter::UP, sizeof(up));
            parameterRight = parameterManager.add(Name+Parameter::RIGHT, sizeof(right));
            parameterFov = parameterManager.add(Name+Parameter::FOV, sizeof(fov));
            parameterZNear = parameterManager.add(Name+Parameter::ZNEAR, sizeof(zNear));
            parameterZFar = parameterManager.add(Name+Parameter::ZFAR, sizeof(zFar));
            parameterView = parameterManager.add(Name+Parameter::VIEW, sizeof(view));
            parameterProjection = parameterManager.add(Name+Parameter::PROJECTION, sizeof(proj));
        }

        virtual void fillParameters() {
            parameterDirection->setValue(&dir);
            parameterTarget->setValue(&target);
            parameterUp->setValue(&up);
            parameterRight->setValue(&right);
            parameterFov->setValue(&fov);
            parameterZNear->setValue(&zNear);
            parameterZFar->setValue(&zFar);
            parameterView->setValue(&view);
            parameterProjection->setValue(&proj);
        }

        void rebuild();

        void calcMouseRay(XMFLOAT3 *rayPos, XMFLOAT3 *rayDir, int x, int y)const;

		inline const XMFLOAT3 &getUp()const {
			return up;
		}

		// normalized, sets right
        __declspec(property(get = getUp)) XMFLOAT3 &Up;

        inline const Entity &getTarget()const {
            return target;
        }

        __declspec(property(get = getTarget)) Entity &Target;

        inline const XMFLOAT3 &getDirection()const {
            return dir;
        }

        __declspec(property(get = getDirection)) XMFLOAT3 &Direction;


        inline const float2 &getScreenSize()const {
            return screenSize;
        }

        inline void setScreenSize(const float2 &screenSize) {
            this->screenSize = screenSize;
            aspect = screenSize.x/screenSize.y;
        }

        inline void setScreenSize(unsigned int w, unsigned int h) {
            screenSize = float2((float)w, (float)h);
            aspect = (float)w/(float)h;
        }

        inline unsigned int getWidth() const {
            return (unsigned int)screenSize.x;
        }

        inline void setWidth(unsigned int val) {
            screenSize.x = (float)val;
            aspect = (float)val/(float)screenSize.y;
        }

        inline unsigned int getHeight() const {
            return (unsigned int)screenSize.y;
        }

        inline void setHeight(unsigned int val) {
            screenSize.y = (float)val;
            aspect = (float)screenSize.x/(float)val;
        }

        inline float getAspect()const {
            return aspect;
        }

        inline const XMFLOAT4X4 *getView()const {
            return &view;
        }

        inline const XMFLOAT4X4 *getProj()const {
            return &proj;
        }

        inline const XMFLOAT4X4 *getFacing()const {
            return &facing;
        }

        inline void setPositionTargetUp(XMFLOAT3 &pos, XMFLOAT3 &target, XMFLOAT3 &up) {
            /*Position = pos;
            
            this->target = target;
            XMVECTOR dv = XMLoadFloat3(&target)-XMLoadFloat3(&pos);
            
            XMStoreFloat(&dist, XMVector3Length(dv));
            XMVECTOR uv = XMLoadFloat3(&up);
            XMStoreFloat3(&dir, XMVector3Normalize(dv));
            XMVECTOR rv = XMVector3Normalize(XMVector3Cross(dv, uv));
            XMStoreFloat3(&right, rv);
            uv = XMVector3Normalize(XMVector3Cross(rv, dv));
            XMStoreFloat3(&this->up, uv);*/
        }

        inline void setPositionDirectionUp(XMFLOAT3 &pos, XMFLOAT3 &dir, XMFLOAT3 &up) {
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

        inline void setViewYawPitchRoll(float yaw, float pitch, float roll) {
            /*XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
            XMVECTOR dv = XMVectorSet(0, 0, dist==0?-1:-dist, 0);
            dv = XMVector3Transform(dv, rotation);
            XMStoreFloat3(&target, XMLoadFloat3(&Position)+dv);
			XMStoreFloat3(&dir, XMVector4Normalize(dv));
            XMStoreFloat3(&up, XMVector3Transform(XMVectorSet(0, 1, 0, 0), rotation));
            XMStoreFloat3(&right, XMVector3Transform(XMVectorSet(1, 0, 0, 0), rotation));*/
        }

        inline void setOrbitYawPitchRoll(float yaw, float pitch, float roll) {
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

        /**
        * Testuje sfer? z bry?? widzenia kamery. Kamera musi zosta?
        * wcze?niej prawid?o zbudowana
        * @param XMFLOAT3 * center ?rodek testowanej sfery
        * @param float radius promie? testowanej sfery
        * @return bool czy sfera jest w bryle widzenia
        */
        /*inline bool sphereTest(XMFLOAT3 *center,float radius){
        XMFLOAT3 out;
        D3DXVec3TransformCoord(&out,center,&(view*proj));
        if(out.x-radius>screenSize.x||out.x+radius<0||
        out.y-radius>screenSize.y||out.y+radius<0||
        out.z-radius>zFar||out.z+radius<zNear)
        return false;
        return true;
        }*/
    };
}