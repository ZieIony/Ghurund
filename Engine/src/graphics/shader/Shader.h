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

#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Shader:public Resource {
    private:
        ShaderProgram *programs[6] = {};
        ComPtr<ID3D12RootSignature> rootSignature;
        ComPtr<ID3D12PipelineState> pipelineState;

		List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;
        
		unsigned int compileShaders = ShaderType::VS|ShaderType::PS;
        char *source = nullptr;
        bool compiled = false;

        Status makeRootSignature(Graphics &graphics);
        Status makePipelineState(Graphics &graphics);

        void initConstants(Graphics &graphics, ParameterManager &parameterManager);
        void initConstants(Graphics &graphics, ParameterManager &parameterManager, ShaderProgram &program);

        Status loadShd(ResourceManager &resourceManager, MemoryInputStream &stream);
        Status loadHlsl(ResourceManager &resourceManager, MemoryInputStream &stream);

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override;

    public:

        Shader() {}

        ~Shader() {
            constantBuffers.deleteItems();
            textureBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
            for(size_t i = 0; i<6; i++)
                delete programs[i];
            delete[] source;
        }

        Status compile(char **outErrorMessages = nullptr);

        Status build(ResourceManager &resourceManager, char **outErrorMessages = nullptr) {
            Status result;
            if(!compiled)
                if((result = compile(outErrorMessages))!=Status::OK)
                    return result;
            Graphics &graphics = resourceManager.Graphics;
            initConstants(graphics, resourceManager.ParameterManager);
			if((result = makeRootSignature(graphics))!=Status::OK)
                return result;
            return makePipelineState(graphics);
        }

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        size_t getParametersCount() {
            return constantBuffers.Size+textureBuffers.Size+textures.Size;
        }

        bool getCompileShader(ShaderType type) {
            return ((unsigned int)compileShaders&(unsigned int)type)!=0;
        }

        void setCompileShaders(ShaderType types) {
            if(compileShaders!=types) {
                compileShaders = types;
                compiled = false;
            }
        }

        void setSourceCode(const char *source) {
            safeCopyStrA(&this->source, source);
            compiled = false;
        }

        const char *getSourceCode() {
            return source;
        }

        void set(CommandList &commandList, ParameterManager &parameterManager) {
            commandList.get()->SetPipelineState(pipelineState.Get());
            commandList.get()->SetGraphicsRootSignature(rootSignature.Get());

            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->set(commandList, parameterManager);
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