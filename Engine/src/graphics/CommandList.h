#pragma once

#include "Fence.h"
#include "Graphics.h"
#include "core/NamedObject.h"
#include "core/collection/PointerList.h"

namespace Ghurund {
    enum class CommandListState {
        INVALID,
        RECORDING,  // can be closed
        CLOSED, // executing, can be waited for
        FINISHED    // can be only reset
    };

    class CommandList: public NamedObject, public Pointer {
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
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<CommandList>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CommandList))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

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
            commandList->SetName(name);
        }

        bool setPipelineState(ID3D12PipelineState* pipelineState);

        bool setGraphicsRootSignature(ID3D12RootSignature* rootSignature);

        inline void barrier(const D3D12_RESOURCE_BARRIER& barrier) {
            commandList->ResourceBarrier(1, &barrier);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        void addResourceRef(ID3D12Object* resource) {
            resource->AddRef();
            resourceRefs.add(resource);
        }

        void addPointerRef(Pointer* resource) {
            pointerRefs.add(resource);
        }
    };
}