#pragma once

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund {
	using namespace DirectX;

	class ShaderConstant {
    protected:
        AString name;
        unsigned int bindPoint, bindSlot;
        D3D12_SHADER_VISIBILITY visibility;

    public:
        ShaderConstant(const AString& name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility) {
            this->name = name;
            this->bindPoint = bindPoint;
            this->visibility = visibility;
        }

        inline const AString& getName() {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

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