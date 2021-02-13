#pragma once

#include "core/io/MemoryStream.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"
#include "graphics/Graphics.h"
#include "ecs/Entity.h"
#include "resource/Resource.h"
#include "game/TransformComponent.h"

namespace Ghurund {

    class Camera: public Entity, public ParameterProvider {
    private:
        TransformComponent* transformComponent;
		
		XMFLOAT3 target, dir, right, up;
        XMFLOAT4X4 view, proj, viewProj, viewProjInv, facing;
        XMINT2 screenSize;
        float fov, zNear, zFar, dist;
        bool pers;

        ValueParameter* parameterDirection = nullptr, *parameterPosition;
        ValueParameter* parameterUp, * parameterRight;
        ValueParameter* parameterFov;
        ValueParameter* parameterZNear, * parameterZFar;
        ValueParameter* parameterView, * parameterProjection, * parameterViewProjection, * parameterViewProjectionInv;

        PointerArray<Parameter*> parameters;

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<Camera>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Camera))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:

        Camera();

		~Camera() {
			transformComponent->release();
		}

        virtual void initParameters(ParameterManager& parameterManager);

        virtual void updateParameters();

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        void rebuild();

        void calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir) const;

        inline const XMFLOAT3& getUp() const {
            return up;
        }

        // normalized, sets right
        __declspec(property(get = getUp)) XMFLOAT3& Up;

        inline const XMFLOAT3& getTarget() const {
            return target;
        }

        __declspec(property(get = getTarget)) XMFLOAT3& Target;

        inline const XMFLOAT3& getDirection() const {
            return dir;
        }

        __declspec(property(get = getDirection)) XMFLOAT3& Direction;

        inline const XMFLOAT3& getRight() const {
            return right;
        }

        __declspec(property(get = getRight)) XMFLOAT3& Right;


        inline const XMINT2& getScreenSize() const {
            return screenSize;
        }

        inline void setScreenSize(const XMINT2& screenSize) {
            this->screenSize = screenSize;
        }

        inline void setScreenSize(unsigned int w, unsigned int h) {
            screenSize = XMINT2(w, h);
        }

        __declspec(property(get = getScreenSize, put = setScreenSize)) XMINT2& ScreenSize;

        inline unsigned int getWidth() const {
            return screenSize.x;
        }

        inline void setWidth(unsigned int val) {
            screenSize.x = val;
        }

        __declspec(property(get = getWidth, put = setWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return screenSize.y;
        }

        inline void setHeight(unsigned int val) {
            screenSize.y = val;
        }

        __declspec(property(get = getHeight, put = setHeight)) unsigned int Height;

        inline float getAspect() const {
            return (float)screenSize.x / (float)screenSize.y;
        }

        __declspec(property(get = getAspect)) float Aspect;

        inline float getDistance() const {
            return dist;
        }

        __declspec(property(get = getDistance)) float Distance;

        inline const XMFLOAT4X4& getView() const {
            return view;
        }

        __declspec(property(get = getView)) XMFLOAT4X4& View;

        inline const XMFLOAT4X4& getProjection() const {
            return proj;
        }

        __declspec(property(get = getProjection)) XMFLOAT4X4& Projection;

        inline const XMFLOAT4X4& getViewProjection() const {
            return viewProj;
        }

        __declspec(property(get = getViewProjection)) XMFLOAT4X4& ViewProjection;

        inline const XMFLOAT4X4& getViewProjectionInv() const {
            return viewProjInv;
        }

        __declspec(property(get = getViewProjectionInv)) XMFLOAT4X4& ViewProjectionInv;

        inline const XMFLOAT4X4& getFacing() const {
            return facing;
        }

        __declspec(property(get = getFacing)) XMFLOAT4X4& Facing;

        inline bool getPerspective() const {
            return pers;
        }

        inline void setPerspective(bool pers) {
            this->pers = pers;
            notifyObjectChanged();
        }

        __declspec(property(get = getPerspective, put = setPerspective)) bool Perspective;

        void setPositionTargetUp(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up = XMFLOAT3(0, 1, 0));
        void setPositionDirectionDistanceUp(const XMFLOAT3& pos, const XMFLOAT3& dir, float dist = 1.0f, const XMFLOAT3& up = XMFLOAT3(0, 1, 0));

        inline XMFLOAT3 getRotation() const {
            float currentYaw = (float)(atan2(dir.x, dir.z) + XM_PI);
            float currentPitch = atan2f(dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
            float currentRoll = atan2f(right.y, 1);

            return XMFLOAT3(currentYaw, currentPitch, currentRoll);
        }

        void setRotation(float yaw, float pitch, float roll = 0.0f);
        void setOrbit(float yaw, float pitch, float roll = 0.0f);
        void rotate(float yaw, float pitch, float roll = 0.0f);
        void orbit(float yaw, float pitch, float roll = 0.0f);
        void pan(float x, float y);
        void zoom(float z);

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::ENTITY};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}