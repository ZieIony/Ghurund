#pragma once

#include "resource/Resource.h"
#include "core/collection/List.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"
#include "ShaderType.h"
#include "resource/ResourceManager.h"
#include "CompilationTarget.h"
#include "ShaderProgram.h"
#include "resource/ResourceContext.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund {
    using namespace Microsoft::WRL;

    class Shader:public Resource, public ParameterProvider {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Shader);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Shader>();

        ShaderProgram* programs[6] = {};
        ID3D12RootSignature* rootSignature;
        ID3D12PipelineState* pipelineState;
        bool supportsTransparency = false;

        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;

        PointerArray<Parameter*>* parameters = nullptr;
#ifdef _DEBUG
        bool* reported;
#endif

        Graphics* graphics;

        AString source;
        bool compiled = false;

        Status makeRootSignature();

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        void initConstants(ParameterManager& parameterManager);
        void initConstants(ParameterManager& parameterManager, ShaderProgram& program);

        Status loadShd(ResourceContext& context, MemoryInputStream& stream);
        Status loadHlsl(ResourceContext& context, MemoryInputStream& stream);

        void finalize();

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, CLASS_NAME)
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

        virtual unsigned int getVersion() const override {
            return 0;
        }

    public:
        ~Shader();

        virtual void reload(ResourceContext& context);

        virtual void invalidate();

        virtual bool isValid() const {
            return pipelineState != nullptr && rootSignature != nullptr && compiled && __super::isValid();
        }

        Status compile(char** output = nullptr);

        Status build(ResourceContext& context, char** output = nullptr);

        virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override {
            for (size_t i = 0; i < constantBuffers.Size; i++)
                constantBuffers[i]->updateParameters();
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return *parameters;
        }

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = { (ResourceFormat*)&ResourceFormat::SHADER, (ResourceFormat*)&ResourceFormat::HLSL };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}