#pragma once

#include "Texture.h"
#include "core/SharedPointer.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

        static Texture* make(Graphics& graphics, CommandList& commandList, ResourceManager& manager, const wchar_t* fileName) {
            auto path = std::format(L"{}{}{}", ResourceManager::LIB_PROTOCOL, ResourceManager::ENGINE_LIB_NAME, fileName);
            return makeFromImage(graphics, commandList, manager, FilePath(path.c_str()));
        }

    public:
        static Texture* makeDefaultDiffuse(Graphics& graphics, CommandList& commandList, ResourceManager& manager) {
            return make(graphics, commandList, manager, L"/textures/diffuse.png");
        }

        static Texture* makeDefaultSpecular(Graphics& graphics, CommandList& commandList, ResourceManager& manager) {
            return make(graphics, commandList, manager, L"/textures/specular.png");
        }

        static Texture* makeDefaultNormal(Graphics& graphics, CommandList& commandList, ResourceManager& manager) {
            return make(graphics, commandList, manager, L"/textures/normal.png");
        }

        static Texture* makeChecker(Graphics& graphics, CommandList& commandList, ResourceManager& manager) {
            return make(graphics, commandList, manager, L"/textures/checker.png");
        }

        static Texture* makeFromImage(Graphics& graphics, CommandList& commandList, ResourceManager& manager, const FilePath& imagePath) {
            Ghurund::Core::Image* image = manager.load<Ghurund::Core::Image>(imagePath);
            if (image == nullptr)
                return nullptr;
            Texture* texture = ghnew Texture();
            texture->init(graphics, commandList, *image);
            image->release();
            return texture;
        }
    };
}