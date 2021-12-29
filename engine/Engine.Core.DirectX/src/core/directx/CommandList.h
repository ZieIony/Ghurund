#pragma once

#include "Fence.h"
#include "Graphics.h"
#include "core/NamedObject.h"
#include "core/collection/PointerList.h"
#include "core/logging/Formatter.h"

#include <format>

namespace Ghurund::Core::DirectX {
    enum class CommandListState {
        INVALID,
        RECORDING,  // can be closed
        CLOSED, // executing, can be waited for
        FINISHED    // can be only reset
    };

    class CommandList: public NamedObject<wchar_t>, public Pointer {
    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ID3D12CommandQueue* commandQueue = nullptr;
        CommandListState state = CommandListState::INVALID;

        ID3D12PipelineState* pipelineState = nullptr;
        ID3D12RootSignature* rootSignature = nullptr;

        List<ID3D12Object*> resourceRefs;
        PointerList<Pointer*> pointerRefs;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:

        CommandList() {
#ifdef _DEBUG
            Name = L"unnamed CommandList";
#endif
        }

        ~CommandList();

        Status init(Graphics& graphics, ID3D12CommandQueue* queue);

        Status wait();

        Status reset();

        Status finish();

        inline ID3D12GraphicsCommandList* get() {
            return commandList.Get();
        }

        inline CommandListState getState() {
            return state;
        }

        __declspec(property(get = getState)) CommandListState State;

        virtual void setName(const WString& name) override {
            NamedObject::setName(name);
            commandList->SetName(name.Data);
        }

        bool setPipelineState(ID3D12PipelineState* pipelineState);

        bool setGraphicsRootSignature(ID3D12RootSignature* rootSignature);

        inline void barrier(const D3D12_RESOURCE_BARRIER& barrier) {
            commandList->ResourceBarrier(1, &barrier);
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        void addResourceRef(ID3D12Object* resource) {
            resource->AddRef();
            resourceRefs.add(resource);
        }

        void addPointerRef(Pointer* resource) {
            pointerRefs.add(resource);
        }

        virtual String toString() const override {
            return String(std::format(_T("{}: {\n}\n"), __super::toString()).c_str());
        }
    };
}