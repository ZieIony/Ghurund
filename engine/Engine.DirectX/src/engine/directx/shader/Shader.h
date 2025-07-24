#pragma once

#include "CompilationTarget.h"
#include "ConstantBuffer.h"
#include "core/collection/List.h"
#include <core/Buffer.h>
#include <core/object/OwnedNotNull.h>
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"
#include "Sampler.h"
#include "ShaderProgram.h"
#include "ShaderType.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;

    struct ShaderConstants {
        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;

        ~ShaderConstants() {
            clear();
        }

        void clear() {
            constantBuffers.deleteItems();
            textureBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
        }
    };

    class Shader:public Resource//, public ParameterProvider
    {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Shader::GET_TYPE();
#pragma endregion

    private:
        ID3D12RootSignature* rootSignature = nullptr;
        ID3D12PipelineState* pipelineState = nullptr;
        ShaderConstants* constants = nullptr;
        bool supportsTransparency = false;

        //PointerArray<Parameter*>* parameters = nullptr;
#ifdef _DEBUG
        bool* reported = nullptr;
#endif

        //void initConstants(ParameterManager& parameterManager);
        //void initConstants(ParameterManager& parameterManager, ShaderProgram& program);

        void finalize();

    public:
        ~Shader();

        virtual void invalidate() override;

        virtual bool isValid() const {
            return pipelineState != nullptr && rootSignature != nullptr && __super::isValid();
        }

        void init(OwnedNotNull<ID3D12RootSignature> rootSignature, OwnedNotNull<ID3D12PipelineState> pipelineState, OwnedNotNull<ShaderConstants> constants) {
            this->rootSignature = &rootSignature;
            this->pipelineState = &pipelineState;
            this->constants = &constants;
        }

        /*virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override {
            for (size_t i = 0; i < constantBuffers.Size; i++)
                constantBuffers[i]->updateParameters();
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return *parameters;
        }*/

        bool set(Graphics& graphics, CommandList& commandList);

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        __declspec(property(get = getSupportsTransparency)) bool SupportsTransparency;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Shader::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SHADER = ResourceFormat(L"shader", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SHADER, FORMAT_HLSL };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}