#pragma once

#include "core/resource/Resource.h"
#include "camera/Camera2D.h"

namespace Ghurund::Engine::_2D {
    class Scene2D:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene2D::GET_TYPE();
#pragma endregion

    private:
        Camera2D* camera = nullptr;

    public:
        Scene2D() {
            camera = ghnew Camera2D();
		}

        ~Scene2D() {
            if (camera)
                camera->release();
        }

        inline Camera2D* getCamera() const {
            return camera;
        }

        inline void setCamera(Camera2D* camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera2D* Camera;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene2D::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}