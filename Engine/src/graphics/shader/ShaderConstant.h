#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

namespace Ghurund {
	using namespace DirectX;
	using namespace Microsoft::WRL;

	class ShaderConstant {
    protected:
        char *name = nullptr;
        unsigned int bindPoint, bindSlot;
        D3D12_SHADER_VISIBILITY visibility;

    public:
        ShaderConstant(const char *name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility) {
            this->name = copyStr(name);
            this->bindPoint = bindPoint;
            this->visibility = visibility;
        }

        virtual ~ShaderConstant() {
            delete[] name;
        }

        inline const char *getName() {
            return name;
        }

        __declspec(property(get = getName)) const char* Name;

        inline unsigned int getBindPoint() const {
            return bindPoint;
        }

        inline unsigned int getBindSlot() const {
            return bindSlot;
        }

        inline void setBindSlot(unsigned int slot) {
            bindSlot = slot;
        }

        __declspec(property(get = getBindSlot, put = setBindSlot)) unsigned int BindSlot;

        inline D3D12_SHADER_VISIBILITY getVisibility() const {
            return visibility;
        }

        inline void setVisibility(D3D12_SHADER_VISIBILITY visibility) {
            this->visibility = visibility;
        }

        __declspec(property(get = getVisibility, put = setVisibility)) D3D12_SHADER_VISIBILITY Visibility;

    };
}