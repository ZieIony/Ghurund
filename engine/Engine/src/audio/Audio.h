#pragma once

#include "Common.h"
#include "Status.h"
#include "core/application/Feature.h"

#include <wrl\client.h>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <x3daudio.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <DirectXMath.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

namespace Ghurund::Audio {
    using namespace ::DirectX;
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;

    class Audio:public Feature {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        ComPtr<IXAudio2> device;
        IXAudio2MasteringVoice* masteringVoice = nullptr;
        ComPtr<IMFAttributes> sourceReaderConfiguration;

        X3DAUDIO_HANDLE x3DInstance;
        X3DAUDIO_LISTENER listener = { };	// player's position

    public:
        virtual void onInit() override;

        virtual void onUninit() override;

        ComPtr<IXAudio2> getDevice() {
            return device;
        }

        __declspec(property(get = getDevice)) ComPtr<IXAudio2> Device;

        ComPtr<IMFAttributes> getReaderConfiguration() {
            return sourceReaderConfiguration;
        }

        __declspec(property(get = getReaderConfiguration)) ComPtr<IMFAttributes> ReaderConfiguration;

        void setPosition(const XMFLOAT3& pos) {
            listener.Position.x = pos.x;
            listener.Position.y = pos.y;
            listener.Position.z = pos.z;
        }

        XMFLOAT3 getPosition() const {
            return XMFLOAT3(listener.Position.x, listener.Position.y, listener.Position.z);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

        void setVelocity(const XMFLOAT3& vel) {
            listener.Velocity.x = vel.x;
            listener.Velocity.y = vel.y;
            listener.Velocity.z = vel.z;
        }

        XMFLOAT3 getVelocity() const {
            return XMFLOAT3(listener.Position.x, listener.Velocity.y, listener.Velocity.z);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT3 Velocity;

        void setDirection(const XMFLOAT3& dir) {
            listener.OrientFront.x = dir.x;
            listener.OrientFront.y = dir.y;
            listener.OrientFront.z = dir.z;
        }

        XMFLOAT3 getDirection() const {
            return XMFLOAT3(listener.OrientFront.x, listener.OrientFront.y, listener.OrientFront.z);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        void setUp(const XMFLOAT3& up) {
            listener.OrientTop.x = up.x;
            listener.OrientTop.y = up.y;
            listener.OrientTop.z = up.z;
        }

        XMFLOAT3 getUp() const {
            return XMFLOAT3(listener.OrientTop.x, listener.OrientTop.y, listener.OrientTop.z);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        void calculate3D(X3DAUDIO_EMITTER& emitter) {
            X3DAUDIO_DSP_SETTINGS pDSPSettings = {};
            X3DAudioCalculate(x3DInstance, &listener, &emitter, 0, &pDSPSettings);
        }
    };
}