#pragma once

#include "Entity3D.h"

#include "core/resource/Resource.h"
#include "camera/Camera3D.h"

namespace Ghurund::Engine::_3D {
    class Scene3D:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene3D::GET_TYPE();
#pragma endregion

    private:
        Camera3D* camera = nullptr;
        List<IntrusivePointer<Entity3D>> entities;

    public:
        Scene3D() {
            camera = ghnew Camera3D();
        }

        ~Scene3D() {
            if (camera)
                camera->release();
        }

        inline Camera3D* getCamera() const {
            return camera;
        }

        inline void setCamera(Camera3D* camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera3D* Camera;

        inline void add(IntrusivePointer<Entity3D> entity) {
            entities.add(entity);
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene3D::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}
