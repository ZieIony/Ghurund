#pragma once

#include "Fence.h"
#include "core/Logger.h"
#include "Graphics.h"
#include "core/NamedObject.h"
#include "collection/PointerList.h"

namespace Ghurund {
    class Shader;
    class Resource;

    class CommandList: public NamedObject, public Pointer {
    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandQueue> commandQueue;
        bool closed = false;

        ID3D12PipelineState *pipelineState = nullptr;
        ID3D12RootSignature *rootSignature = nullptr; // no need to ref count or cleanup - it's just a tag

        PointerList<Pointer*> resourceRefs;

    public:

        CommandList() {
#ifdef _DEBUG
            Name = _T("unnamed CommandList");
#endif
        }

        ~CommandList();

        Status init(Graphics &graphics, ComPtr<ID3D12CommandQueue> &queue);

        Status wait();

        Status reset();

        Status finish();

        inline ID3D12GraphicsCommandList *get() {
            return commandList.Get();
        }

        inline bool isClosed() {
            return closed;
        }

        __declspec(property(get = isClosed)) bool Closed;

        virtual void setName(const String &name) override {
            NamedObject::setName(name);
            commandList->SetName(name);
        }

        void setPipelineState(ID3D12PipelineState *pipelineState);

        void setGraphicsRootSignature(ID3D12RootSignature *rootSignature);

        void addResourceRef(Resource &resource);

        bool references(const Resource &resource);

        virtual const Ghurund::Type &getType() const override {
            return Type::COMMAND_LIST;
        }
    };
}