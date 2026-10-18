#pragma once

#include "core/image/Image.h"
#include "engine/directx/buffer/DescriptorHeap.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/cubemap/ICubeMap.h"

namespace Ghurund::Engine::DirectX {
    class DxCubeMap:public ICubeMap {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxCubeMap::GET_TYPE();
#pragma endregion

    private:
		ComPtr<ID3D12Resource> textureResource;
        DescriptorHandle descHandle;
        DXGI_FORMAT format;

        List<IntrusivePointer<Ghurund::Core::Image>> imagesTop;
        List<IntrusivePointer<Ghurund::Core::Image>> imagesBottom;
        List<IntrusivePointer<Ghurund::Core::Image>> imagesLeft;
        List<IntrusivePointer<Ghurund::Core::Image>> imagesRight;
        List<IntrusivePointer<Ghurund::Core::Image>> imagesFront;
        List<IntrusivePointer<Ghurund::Core::Image>> imagesBack;

        inline void unload_internal() {
            imagesTop.clear();
            imagesBottom.clear();
            imagesLeft.clear();
            imagesRight.clear();
            imagesFront.clear();
            imagesBack.clear();
            dataSize.system = sizeof(*this);
        }

        inline void deinit_internal() {
            textureResource.Reset();
        }

    protected:
        ~DxCubeMap() {}

    public:
        void init(class DxGPUMemoryManager& memoryManager);

        inline void deinit() {
            if (State != ResourceState::INITIALIZED)
                return;
            deinit_internal();
            State = ResourceState::LOADED;
        }

        inline void unload() {
            if (State != ResourceState::LOADED)
                return;
            unload_internal();
            State = ResourceState::EMPTY;
        }

        inline DXGI_FORMAT getFormat() const {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        void setImages(
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesTop,
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesBottom,
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesLeft,
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesRight,
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesFront,
            List<IntrusivePointer<Ghurund::Core::Image>>& imagesBack
        );

        /*inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;*/

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxCubeMap::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD, 1);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion
    };
}
