#pragma once

#include "Graphics.h"
#include "core/MemoryStream.h"
#include "resource/Resource.h"
#include "game/ParameterProvider.h"
#include "game/Parameter.h"
#include "game/Entity.h"
#include "game/Target.h"

namespace Ghurund {

    class Camera: public Entity {
    private:
        Target target;
        XMFLOAT3 dir, right, up;
        XMFLOAT4X4 view, proj, viewProj, facing;
        XMFLOAT2 screenSize;
        float fov, zNear, zFar, dist;
        bool pers;

        Parameter *parameterDirection;
        Parameter *parameterUp,*parameterRight;
        Parameter *parameterFov;
        Parameter *parameterZNear,*parameterZFar;
        Parameter *parameterView, *parameterProjection, *parameterViewProjection;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead);
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const;

        virtual void clean() {}

    public:

        Camera();

        virtual EntityType getType() const override {
            return EntityType::CAMERA;
        }

        virtual void initParameters(ParameterManager &parameterManager);

        virtual void fillParameters();

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


        inline const XMFLOAT2 &getScreenSize()const {
            return screenSize;
        }

        inline void setScreenSize(const XMFLOAT2 &screenSize) {
            this->screenSize = screenSize;
        }

        inline void setScreenSize(unsigned int w, unsigned int h) {
            screenSize = XMFLOAT2((float)w, (float)h);
        }

        inline unsigned int getWidth() const {
            return (unsigned int)screenSize.x;
        }

        inline void setWidth(unsigned int val) {
            screenSize.x = (float)val;
        }

        inline unsigned int getHeight() const {
            return (unsigned int)screenSize.y;
        }

        inline void setHeight(unsigned int val) {
            screenSize.y = (float)val;
        }

        inline float getAspect()const {
            return screenSize.x/screenSize.y;
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

        void setPositionTargetUp(XMFLOAT3 &pos, XMFLOAT3 &target, XMFLOAT3 &up);

        void setPositionDirectionUp(XMFLOAT3 &pos, XMFLOAT3 &dir, XMFLOAT3 &up);

        void setViewYawPitchRoll(float yaw, float pitch, float roll);

        void setOrbitYawPitchRoll(float yaw, float pitch, float roll);

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

        void defaultLookAt(Entity *entity) {

        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }
    };
}