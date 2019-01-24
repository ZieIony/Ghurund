#pragma once

#include "core/MemoryStream.h"
#include "game/entity/Entity.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/Parameter.h"
#include "graphics/Graphics.h"
#include "resource/Resource.h"

namespace Ghurund {

    class Camera: public Entity {
    private:
        XMFLOAT3 pos, target, dir, right, up;
        XMFLOAT4X4 view, proj, viewProj, facing;
        XMFLOAT2 screenSize;
        float fov, zNear, zFar, dist;
        bool pers;

        Parameter *parameterDirection = nullptr;
        Parameter *parameterUp, *parameterRight;
        Parameter *parameterFov;
        Parameter *parameterZNear, *parameterZFar;
        Parameter *parameterView, *parameterProjection, *parameterViewProjection;

        Array<Parameter*> parameters;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options);
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const;

    public:

        Camera();

        virtual const Ghurund::Type &getType() const override {
            return Type::CAMERA;
        }

        virtual void initParameters(ParameterManager &parameterManager);

        virtual void updateParameters();

        virtual Array<Parameter*> &getParameters() override {
            return parameters;
        }

        void rebuild();

        void calcMouseRay(const XMINT2 &mousePos, XMFLOAT3 &rayPos, XMFLOAT3 &rayDir) const;

        inline const XMFLOAT3 &getUp() const {
            return up;
        }

        // normalized, sets right
        __declspec(property(get = getUp)) XMFLOAT3 &Up;

        inline const XMFLOAT3 &getPosition() const {
            return pos;
        }

        __declspec(property(get = getPosition)) XMFLOAT3 &Position;

        inline const XMFLOAT3 &getTarget() const {
            return target;
        }

        __declspec(property(get = getTarget)) XMFLOAT3 &Target;

        inline const XMFLOAT3 &getDirection() const {
            return dir;
        }

        __declspec(property(get = getDirection)) XMFLOAT3 &Direction;


        inline const XMFLOAT2 &getScreenSize() const {
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

        __declspec(property(get = getWidth, put = setWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return (unsigned int)screenSize.y;
        }

        inline void setHeight(unsigned int val) {
            screenSize.y = (float)val;
        }

        __declspec(property(get = getHeight, put = setHeight)) unsigned int Height;

        inline float getAspect() const {
            return screenSize.x/screenSize.y;
        }

        __declspec(property(get = getAspect)) float Aspect;

        inline float getDistance() const {
            return dist;
        }

        __declspec(property(get = getDistance)) float Distance;

        inline const XMFLOAT4X4 *getView() const {
            return &view;
        }

        __declspec(property(get = getView)) XMFLOAT4X4 *View;

        inline const XMFLOAT4X4 *getProjection() const {
            return &proj;
        }

        __declspec(property(get = getProjection)) XMFLOAT4X4 *Projection;

        inline const XMFLOAT4X4 *getFacing() const {
            return &facing;
        }

        __declspec(property(get = getFacing)) XMFLOAT4X4 *Facing;

        inline bool getPerspective() const {
            return pers;
        }

        inline void setPerspective(bool pers) {
            this->pers = pers;
            notifyObjectChanged();
        }

        __declspec(property(get = getPerspective, put = setPerspective)) bool Perspective;

        void setPositionTargetUp(const XMFLOAT3 &pos, const XMFLOAT3 &target, const XMFLOAT3 &up = XMFLOAT3(0, 1, 0));
        void setPositionDirectionUp(const XMFLOAT3 &pos, const XMFLOAT3 &dir, const XMFLOAT3 &up = XMFLOAT3(0, 1, 0));
        void setPositionDistanceRotation(const XMFLOAT3 &pos, float dist, float yaw, float pitch, float roll = 0.0f);
        void setTargetDistanceOrbit(const XMFLOAT3 &target, float dist, float yaw, float pitch, float roll = 0.0f);

        inline XMFLOAT3 getRotation() const {
            float currentYaw = atan2(dir.x, dir.z)+XM_PI;
            float currentPitch = atan2f(dir.y, sqrtf(dir.x*dir.x+dir.z*dir.z));
            float currentRoll = atan2f(right.y, 1);

            return XMFLOAT3(currentYaw, currentPitch, currentRoll);
        }

        void setRotation(float yaw, float pitch, float roll = 0.0f);
        void setOrbit(float yaw, float pitch, float roll = 0.0f);
        void rotate(float yaw, float pitch, float roll = 0.0f);
        void orbit(float yaw, float pitch, float roll = 0.0f);
        void pan(float x, float y);
        void zoom(float z);

        void defaultLookAt(Entity *entity) {

        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::ENTITY};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override {}
    };
}