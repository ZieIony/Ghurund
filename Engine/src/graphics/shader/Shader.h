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
            void *byteCode;
            unsigned int byteCodeLength;
            char *entryPoint = nullptr;
            ShaderType &type;
            CompilationTarget target;

			ShaderProgram(ShaderType &type, const char *entryPoint = nullptr, CompilationTarget target = CompilationTarget::SHADER_5_0) : type(type) {
                setEntryPoint(entryPoint);
                setCompilationTarget(target);
            }

            ~ShaderProgram() {
                delete[] entryPoint;
            }

            Status compile(const char *code, char **outErrorMessages);

            const char *makeCompilationTarget() {
                const char *targetText = nullptr;
                switch(target) {
                    case CompilationTarget::SHADER_5_0:
                        targetText = "5_0";
                        break;
                }
                const char *typeText = type.toString();
                char *text = ghnew char[10];;
                sprintf_s(text, 10, "%s_%s", typeText, targetText);
                return text;
            }

            void setEntryPoint(const char *entryPoint) {
                if(entryPoint == nullptr) {
                    safeCopyStrA(&this->entryPoint, type.getEntryPoint());
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

            void *getByteCode() {
                return byteCode;
            }

            unsigned int getByteCodeLength() {
                return byteCodeLength;
            }

            D3D12_INPUT_LAYOUT_DESC getInputLayout();
        };

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

    protected:
        virtual unsigned int getVersion()const {
            return 1;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const;

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
    };
}