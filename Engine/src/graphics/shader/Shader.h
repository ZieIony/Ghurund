#pragma once

#include "Ghurund.h"
#include "resource/Resource.h"
#include "collection/List.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"
#include "ShaderType.h"

#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    enum class CompilationTarget {
        SHADER_5_0
    };

    class Shader:public Resource {
    private:
        struct ShaderProgram {
            ComPtr<ID3DBlob> shader;
            CD3DX12_SHADER_BYTECODE byteCode;
            char *entryPoint = nullptr;
            ShaderType type;
            CompilationTarget target;

            ShaderProgram(ShaderType type, const char *entryPoint = nullptr, CompilationTarget target = CompilationTarget::SHADER_5_0) {
                this->type = type;
                setEntryPoint(entryPoint);
                setCompilationTarget(target);
            }

            ~ShaderProgram() {
                delete[] entryPoint;
            }

            Status compile(const char *code, char **outErrorMessages);

            static const char *getDefaultEntryPoint(ShaderType type) {
                switch(type) {
                    case ShaderType::VS:
                        return "vertexMain";
                    case ShaderType::PS:
                        return "pixelMain";
                    case ShaderType::GS:
                        return "geometryMain";
                    case ShaderType::HS:
                        return "hullMain";
                    case ShaderType::DS:
                        return "domainMain";
                        //case ShaderType::CS:
                    default:
                        return "computeMain";
                }
            }

            const char *makeCompilationTarget() {
                const char *targetText;
                switch(target) {
                    case CompilationTarget::SHADER_5_0:
                        targetText = "5_0";
                        break;
                }
                const char *typeText = type.toString();
                char *text = ghnew char[10];;
                sprintf_s(text, 10, "%s_%s", targetText, typeText);
                return text;
            }

            D3D12_SHADER_VISIBILITY getVisibilty() {
                switch(type) {
                    case ShaderType::VS:
                        return D3D12_SHADER_VISIBILITY_VERTEX;
                    case ShaderType::PS:
                        return D3D12_SHADER_VISIBILITY_PIXEL;
                    case ShaderType::GS:
                        return D3D12_SHADER_VISIBILITY_GEOMETRY;
                    case ShaderType::HS:
                        return D3D12_SHADER_VISIBILITY_HULL;
                    case ShaderType::DS:
                        return D3D12_SHADER_VISIBILITY_DOMAIN;
                        //case ShaderType::CS:
                    default:
                        return D3D12_SHADER_VISIBILITY_ALL;
                }
            }

            void setEntryPoint(const char *entryPoint) {
                if(entryPoint == nullptr) {
                    safeCopyStrA(&this->entryPoint, getDefaultEntryPoint(type));
                } else {
                    safeCopyStrA(&this->entryPoint, entryPoint);
                }
            }

            const char *getEntryPoint()const {
                return entryPoint;
            }

            void setCompilationTarget(CompilationTarget target) {
                this->target = target;
            }

            CompilationTarget getCompilationTarget()const {
                return target;
            }

            CD3DX12_SHADER_BYTECODE &getByteCode() {
                return byteCode;
            }

            D3D12_INPUT_LAYOUT_DESC getInputLayout();
        };

        ShaderProgram *programs[6];
        ComPtr<ID3D12RootSignature> rootSignature;
        ComPtr<ID3D12PipelineState> pipelineState;
        List<ConstantBuffer*> constantBuffers;
        List<TextureBufferConstant*> textureBuffers;
        List<TextureConstant*> textures;
        List<Sampler*> samplers;
        unsigned int compileShaders = ShaderType::VS|ShaderType::PS;
        char *source;
        bool compiled = false;

        Status makeRootSignature(Graphics &graphics);
        Status makePipelineState(Graphics &graphics);

        void initConstants(Graphics &graphics, ParameterManager &parameterManager);
        void initConstants(Graphics &graphics, ParameterManager &parameterManager, ShaderProgram &program);

    protected:
        virtual unsigned int getVersion()const {
            return 1;
        }

        Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0);

        Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const;

    public:

        Shader() {}

        ~Shader() {
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
        }

        Status compile(char **outErrorMessages);

        Status build(ResourceManager &resourceManager, char **outErrorMessages) {
            Status result;
            if((result = compile(outErrorMessages))!=Status::OK)
                return result;
            Graphics &graphics = resourceManager.Graphics;
            initConstants(graphics, resourceManager.ParameterManager);
            if((result = makeRootSignature(graphics))!=Status::OK)
                return result;
            return makePipelineState(graphics);
        }

        static DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

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

        void setSource(const char *source) {
            safeCopyStrA(&this->source, source);
            compiled = false;
        }

        void set(ID3D12GraphicsCommandList *commandList) {
            commandList->SetPipelineState(pipelineState.Get());
            commandList->SetGraphicsRootSignature(rootSignature.Get());

            for(size_t i = 0; i<constantBuffers.Size; i++)
                constantBuffers[i]->set(commandList);
        }
    };
}