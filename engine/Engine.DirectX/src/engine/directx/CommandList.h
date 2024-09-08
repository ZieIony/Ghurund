#pragma once

#include "Fence.h"
#include "Graphics.h"

namespace Ghurund::Engine::DirectX {
    enum class CommandListState {
        INVALID,
        RECORDING,  // can be closed
        CLOSED, // executing, can be waited for
        FINISHED    // can be only reset
    };

    class CommandList: public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = CommandList::GET_TYPE();
#pragma endregion

    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ID3D12CommandQueue* commandQueue = nullptr;
        CommandListState state = CommandListState::INVALID;

        ID3D12PipelineState* pipelineState = nullptr;
        ID3D12RootSignature* rootSignature = nullptr;

        List<ID3D12Object*> resourceRefs;
        List<RefCountedObject*> pointerRefs;
        WString name;

    public:
        ~CommandList();

        void init(Graphics& graphics, ID3D12CommandQueue* queue);

        void wait();

        void reset();

        void finish();

        inline ID3D12GraphicsCommandList* get() {
            return commandList.Get();
        }

        inline CommandListState getState() {
            return state;
        }

        __declspec(property(get = getState)) CommandListState State;

        inline void setName(const WString& name) {
            this->name = name;
            commandList->SetName(name.Data);
        }

        inline WString getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) WString Name;

        bool setPipelineState(ID3D12PipelineState* pipelineState);

        bool setGraphicsRootSignature(ID3D12RootSignature* rootSignature);

        inline void barrier(const D3D12_RESOURCE_BARRIER& barrier) {
            commandList->ResourceBarrier(1, &barrier);
        }

        void addResourceRef(ID3D12Object* resource) {
            resource->AddRef();
            resourceRefs.add(resource);
        }

        void addPointerRef(RefCountedObject* resource) {
            resource->addReference();
            pointerRefs.add(resource);
        }

        /*virtual String toString() const override {
            return String(std::format(_T("{}: {\n}\n"), __super::toString()).c_str());
        }*/
    };
}