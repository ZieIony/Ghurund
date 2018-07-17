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

        static const List<ResourceFormat> formats;

        Status makeRootSignature(Graphics &graphics);
        Status makePipelineState(Graphics &graphics);

        void initConstants(Graphics &graphics, ParameterManager &parameterManager);
        void initConstants(Graphics &graphics, ParameterManager &parameterManager, ShaderProgram &program);

        Status loadShd(ResourceManager &resourceManager, const void *data, unsigned long size);
        Status loadHlsl(ResourceManager &resourceManager, const void *data, unsigned long size);

    protected:
        virtual unsigned int getVersion()const {
            return 1;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size);
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const;

        virtual void clean() {
            for(size_t i = 0; i<constantBuffers.Size; i++)
                delete constantBuffers[i];
            for(size_t i = 0; i<textureBuffers.Size; i++)
                delete textureBuffers[i];
            for(size_t i = 0; i<textures.Size; i++)
                delete textures[i];
            for(size_t i = 0; i<samplers.Size; i++)
                delete samplers[i];
            for(size_t i = 0; i<6; i++)
                delete programs[i];
            delete[] source;
            source = nullptr;
        }

    public:

        Shader() {}

        ~Shader() {
            clean();
        }

        Status compile(char **outErrorMessages = nullptr);

        Status build(ResourceManager &resourceManager, char **outErrorMessages = nullptr) {
            Status result;
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

        void set(ID3D12GraphicsCommandList *commandList) {
            commandList->SetPipelineState(pipelineState.Get());
            commandList->SetGraphicsRootSignature(rootSignature.Get());

            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->set(commandList);
        }

        virtual const List<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::SHADER;
        }
    };
}