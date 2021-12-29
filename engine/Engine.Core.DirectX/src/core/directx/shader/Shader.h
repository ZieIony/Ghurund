#pragma once

#include "CompilationTarget.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "ShaderProgram.h"
#include "ShaderType.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"
#include "core/collection/List.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;

    class Shader:public Resource//, public ParameterProvider
    {
    private:
        ShaderProgram* programs[6] = {};
        ID3D12RootSignature* rootSignature;
        ID3D12PipelineState* pipelineState;
        bool supportsTransparency = false;

        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;

        //PointerArray<Parameter*>* parameters = nullptr;
#ifdef _DEBUG
        bool* reported;
#endif

        Graphics* graphics;

        AString source;
        bool compiled = false;

        Status makeRootSignature();

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        //void initConstants(ParameterManager& parameterManager);
        //void initConstants(ParameterManager& parameterManager, ShaderProgram& program);

        Status loadShd(MemoryInputStream& stream);
        Status loadHlsl(MemoryInputStream& stream);

        void finalize();

        static const Ghurund::Core::Type& GET_TYPE();

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

        virtual unsigned int getVersion() const override {
            return 0;
        }

    public:
        ~Shader();

        virtual void reload() override;

        virtual void invalidate() override;

        virtual bool isValid() const {
            return pipelineState != nullptr && rootSignature != nullptr && compiled && __super::isValid();
        }

        Status compile(char** output = nullptr);

        Status build(char** output = nullptr);

        /*virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override {
            for (size_t i = 0; i < constantBuffers.Size; i++)
                constantBuffers[i]->updateParameters();
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return *parameters;
        }*/

        void setSourceCode(const AString& source) {
            this->source = source;
            compiled = false;
        }

        const AString& getSourceCode() {
            return source;
        }

        __declspec(property(get = getSourceCode, put = setSourceCode)) const AString& SourceCode;

        Status makePipelineState(bool supportsTransparency);

        bool set(Graphics& graphics, CommandList& commandList);

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        __declspec(property(get = getSupportsTransparency)) bool SupportsTransparency;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"shader", true, true),
                ResourceFormat(L"hlsl", true, false)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}