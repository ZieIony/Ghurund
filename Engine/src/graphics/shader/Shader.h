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
        ShaderProgram *programs[6] = {};
        ID3D12RootSignature *rootSignature;
        ID3D12PipelineState *pipelineState;
        bool supportsTransparency = false;

        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;

        Array<Parameter*> *parameters = nullptr;
        Graphics *graphics;

        char *source = nullptr;
        bool compiled = false;

        Status makeRootSignature();

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        void initConstants(ParameterManager &parameterManager);
        void initConstants(ParameterManager &parameterManager, ShaderProgram &program);

        Status loadShd(ResourceContext &context, MemoryInputStream &stream);
        Status loadHlsl(ResourceContext &context, MemoryInputStream &stream);

        void finalize();

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const override;

        virtual unsigned int getVersion() const override {
            return 0;
        }

    public:
        ~Shader();

        virtual void invalidate();

        virtual bool isValid() const {
            return pipelineState!=nullptr&&rootSignature!=nullptr&&compiled&&__super::isValid();
        }

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
            safeCopyStr(&this->source, source);
            compiled = false;
        }

        const char *getSourceCode() {
            return source;
        }

        __declspec(property(get = getSourceCode, put = setSourceCode)) const char* SourceCode;

        Status makePipelineState(bool supportsTransparency);

        bool set(Graphics &graphics, CommandList &commandList) {
            bool changed = commandList.setGraphicsRootSignature(rootSignature)|commandList.setPipelineState(pipelineState);

            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->set(graphics, commandList);

            return changed;
        }

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        __declspec(property(get = getSupportsTransparency)) bool SupportsTransparency;

        virtual const Ghurund::Type &getType() const override {
            return Type::SHADER;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::SHADER, (ResourceFormat*)&ResourceFormat::HLSL};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;
    };
}