#pragma once

#include "Ghurund.h"
#include "core/Logger.h"
#include "Fence.h"
#include "Graphics.h"
#include "CommandList.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include "resource/Resource.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    struct Vertex {
        XMFLOAT4 position;
        XMFLOAT2 texCoord;
        XMFLOAT4 color;
    };

    class Mesh:public Resource {
    protected:
        void *vertices = nullptr;
        unsigned int vertexSize;
        unsigned int vertexCount;
        UINT32 *indices = nullptr;
        unsigned int indexCount;

        ComPtr<ID3D12Resource> vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;

        ComPtr<ID3D12Resource> vertexUploadHeap;
        ComPtr<ID3D12Resource> indexUploadHeap;

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual void clean() {
            delete[] vertices;
            vertices = nullptr;
            delete[] indices;
            indices = nullptr;
            vertexBuffer.Reset();
            vertexBufferView = {};
            indexBuffer.Reset();
            indexBufferView = {};
            vertexUploadHeap.Reset();
            indexUploadHeap.Reset();
        }

    public:
        ~Mesh() {
            clean();
        }

        Status init(Graphics &graphics, std::shared_ptr<CommandList> commandList);

        void draw(ID3D12GraphicsCommandList *commandList) {
            commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
            commandList->IASetIndexBuffer(&indexBufferView);
            commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
        }
    };
}