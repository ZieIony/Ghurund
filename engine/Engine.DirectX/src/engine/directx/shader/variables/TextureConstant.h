#pragma once

#include "ShaderConstant.h"

#include "engine/directx/CommandList.h"
#include "engine/directx/texture/DxTexture.h"

#include <format>

namespace Ghurund::Engine::DirectX {
    class TextureConstant:public ShaderConstant {
    private:
        DxTexture* texture;

    public:
        TextureConstant(
            const char *name,
            unsigned int bindPoint,
            D3D12_SHADER_VISIBILITY visibility
        ):ShaderConstant(name, bindPoint, visibility) {
        }

        void set(CommandList& commandList) {
            if (!texture) {
                auto text = std::format(_T("Parameter for variable '{}' is missing.\n"), name);
                Logger::log(LogType::WARNING, text.c_str());
                return;
            }
            texture->set(commandList, BindSlot);
        }
    };
}