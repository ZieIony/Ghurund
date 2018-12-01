#pragma once

#include "Ghurund.h"
#include "resource/Resource.h"
#include "collection/List.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"
#include "ShaderType.h"
#include "resource/ResourceManager.h"
#include "CompilationTarget.h"
#include "ShaderProgram.h"
#include "resource/ResourceContext.h"

#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Shader:public Resource, public ParameterProvider {
    private:
        static const char *MAGIC;

        ShaderProgram *programs[6] = {};
        ComPtr<ID3D12RootSignature> rootSignature;
        ComPtr<ID3D12PipelineState> pipelineState;

        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;

        Array<Parameter*> *parameters = nullptr;
        Graphics *graphics;
        PointerList<CommandList*> commandLists;

        char *source = nullptr;
        bool compiled = false;

        Status makeRootSignature(Graphics &graphics);
        Status makePipelineState(Graphics &graphics);

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        void initConstants(Graphics &graphics, ParameterManager &parameterManager);
        void initConstants(Graphics &graphics, ParameterManager &parameterManager, ShaderProgram &program);

        Status loadShd(ResourceContext &context, MemoryInputStream &stream);
        Status loadHlsl(ResourceContext &context, MemoryInputStream &stream);

        void finalize();

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override;

    public:
        ~Shader();

        virtual void invalidate();

        Status compile(char **output = nullptr);

        Status build(ResourceContext &context, char **output = nullptr);

        virtual void initParameters(ParameterManager &parameterManager) override;

        virtual void updateParameters() override {
            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->updateParameters();
        }

        virtual Array<Parameter*> &getParameters() {
            return *parameters;
        }

        void setSourceCode(const char *source) {
            safeCopyStrA(&this->source, source);
            compiled = false;
        }

        const char *getSourceCode() {
            return source;
        }

        void set(CommandList &commandList) {
            commandLists.add(&commandList);
            commandList.addResourceRef(*this);

            commandList.setPipelineState(pipelineState.Get());
            commandList.setGraphicsRootSignature(rootSignature.Get());

            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->set(commandList);
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::SHADER;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::SHADER, ResourceFormat::HLSL};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::SHADER;
        }
    };
}