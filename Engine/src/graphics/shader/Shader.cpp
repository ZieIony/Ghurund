#include "Shader.h"
#include "resource/ResourceManager.h"

namespace Ghurund {

    Status Shader::makeRootSignature(Graphics &graphics) {
        Status result = Status::OK;

        CD3DX12_ROOT_PARAMETER1 *rootParameters = ghnew CD3DX12_ROOT_PARAMETER1[getParametersCount()];
        CD3DX12_DESCRIPTOR_RANGE1 *ranges = ghnew CD3DX12_DESCRIPTOR_RANGE1[getParametersCount()];

        unsigned int r = 0;
        for(size_t i = 0; i<constantBuffers.Size; i++, r++) {
            ShaderConstant *constant = constantBuffers.get(i);
            ranges[r].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, constant->getBindPoint(), 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
            rootParameters[r].InitAsDescriptorTable(1, &ranges[r], constant->getVisibility());
        }

        for(size_t i = 0; i<textures.Size; i++, r++) {
            ShaderConstant *constant = textures.get(i);
            ranges[r].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, constant->getBindPoint(), 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
            rootParameters[r].InitAsDescriptorTable(1, &ranges[r], constant->getVisibility());
        }

        D3D12_STATIC_SAMPLER_DESC *samplerDescs = ghnew D3D12_STATIC_SAMPLER_DESC[samplers.Size];
        for(size_t i = 0; i<samplers.Size; i++)
            samplerDescs[i] = samplers.get(i)->samplerDesc;

        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init_1_1(getParametersCount(),
                                   rootParameters,
                                   samplers.Size,
                                   samplerDescs,
                                   D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        ComPtr<ID3DBlob> signature;
        ComPtr<ID3DBlob> error;
        if(FAILED(D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error))) {
            Logger::log(_T("D3D12SerializeRootSignature() failed\n%hs"), error->GetBufferPointer());
            result = Status::CALL_FAIL;
            goto cleanUp;
        }
        if(FAILED(graphics.getDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)))) {
            Logger::log(_T("device->CreateRootSignature() failed\n"));
            result = Status::CALL_FAIL;
            goto cleanUp;
        }

    cleanUp:
        delete[] rootParameters;
        delete[] ranges;
        delete[] samplerDescs;

        return result;
    }

    Status Shader::makePipelineState(Graphics &graphics) {
        Status result = Status::OK;

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = getInputLayout();
        psoDesc.pRootSignature = rootSignature.Get();
        psoDesc.VS.pShaderBytecode = programs[0]->byteCode;
        psoDesc.VS.BytecodeLength = programs[0]->byteCodeLength;
        psoDesc.PS.pShaderBytecode = programs[1]->byteCode;
        psoDesc.PS.BytecodeLength = programs[1]->byteCodeLength;
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;
        if(FAILED(graphics.getDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)))) {
            Logger::log(_T("device->CreateGraphicsPipelineState() failed\n"));
            result = Status::CALL_FAIL;
        }

        for(unsigned int i = 0; i<psoDesc.InputLayout.NumElements; i++)
            delete[] psoDesc.InputLayout.pInputElementDescs[i].SemanticName;
        delete[] psoDesc.InputLayout.pInputElementDescs;

        return result;
    }

    Status Shader::compile(char **outErrorMessages) {
        ShaderType types[] = {ShaderType::VS, ShaderType::PS, ShaderType::GS, ShaderType::HS, ShaderType::DS, ShaderType::CS};
        ASCIIString errors;
        for(unsigned int i = 0; i<6; i++) {
            if(!getCompileShader(types[i]))
                continue;
            ShaderProgram *program = ghnew ShaderProgram(types[i]);
            char *programErrors;
            Status result = program->compile(source, &programErrors);
            if(result==Status::OK) {
                programs[i] = program;
            } else {
                errors.add(programErrors);
                delete[] programErrors;
                delete program;
            }
        }
        if(errors.Length>0&&outErrorMessages!=nullptr)
            *outErrorMessages = copyStrA(errors.getData());
        compiled = errors.Length==0;
        return compiled ? Status::OK : Status::COMPILATION_ERROR;
    }

    Status Shader::ShaderProgram::compile(const char *code, char **outErrorMessages) {
        unsigned int compileFlags;
#ifdef _DEBUG
        compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        compileFlags = 0;
#endif

        const char *targetText = makeCompilationTarget();
        ID3DBlob *errorBlob;
        Status result;
        ComPtr<ID3DBlob> shader;
        if(FAILED(D3DCompile(code, strlen(code), nullptr, nullptr, nullptr, entryPoint, targetText, compileFlags, 0, &shader, &errorBlob))) {
            if(errorBlob==nullptr) {
                Logger::log(_T("Unknown error while compiling shader\n"));
            } else {
                char *errorMessages = ghnew char[errorBlob->GetBufferSize()];
                memcpy(errorMessages, errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
                Logger::log(_T("Error while compiling shader:\n%hs\n"), errorMessages);
                errorBlob->Release();
                if(outErrorMessages!=nullptr)
                    *outErrorMessages = errorMessages;
            }
            result = Status::COMPILATION_ERROR;
        } else {
            byteCode = ghnew BYTE[shader->GetBufferSize()];
            byteCodeLength = shader->GetBufferSize();
            memcpy(byteCode, shader->GetBufferPointer(), byteCodeLength);
            result = Status::OK;
        }

        delete[] targetText;
        return result;
    }

    DXGI_FORMAT Shader::getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType) {
        if(mask == 1) {
            if(componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32_UINT;
            else if(componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32_SINT;
            else if(componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32_FLOAT;
        } else if(mask <= 3) {
            if(componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32_UINT;
            else if(componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32_SINT;
            else if(componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32_FLOAT;
        } else if(mask <= 7) {
            if(componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32_UINT;
            else if(componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32_SINT;
            else if(componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32_FLOAT;
        } else if(mask <= 15) {
            if(componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32A32_UINT;
            else if(componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32A32_SINT;
            else if(componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    D3D12_INPUT_LAYOUT_DESC Shader::getInputLayout() {
        return programs[0]->getInputLayout();
    }

    D3D12_INPUT_LAYOUT_DESC Shader::ShaderProgram::getInputLayout() {
        ID3D12ShaderReflection* reflector = nullptr;
        D3DReflect(byteCode, byteCodeLength, IID_ID3D12ShaderReflection, (void**)&reflector);
        D3D12_SHADER_DESC desc;
        reflector->GetDesc(&desc);

        D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;
        inputLayoutDesc.NumElements = desc.InputParameters;
        D3D12_INPUT_ELEMENT_DESC *inputElements = ghnew D3D12_INPUT_ELEMENT_DESC[desc.InputParameters];
        for(unsigned int i = 0; i<desc.InputParameters; i++) {
            D3D12_SIGNATURE_PARAMETER_DESC parameterDesc;
            reflector->GetInputParameterDesc(i, &parameterDesc);
            inputElements[i].SemanticName = copyStrA(parameterDesc.SemanticName);
            inputElements[i].SemanticIndex = parameterDesc.SemanticIndex;
            inputElements[i].Format = getFormat(parameterDesc.Mask, parameterDesc.ComponentType);
            inputElements[i].InputSlot = 0;
            inputElements[i].AlignedByteOffset = i==0 ? 0 : D3D12_APPEND_ALIGNED_ELEMENT;
            inputElements[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
        }
        inputLayoutDesc.pInputElementDescs = inputElements;

        reflector->Release();

        return inputLayoutDesc;
    }

    void Shader::initConstants(Graphics &graphics, ParameterManager &parameterManager) {
        for(unsigned int i = 0; i<6; i++)
            if(programs[i]!=nullptr)
                initConstants(graphics, parameterManager, *programs[i]);
    }

    void Shader::initConstants(Graphics &graphics, ParameterManager &parameterManager, ShaderProgram &program) {
        ID3D12ShaderReflection* reflector = nullptr;
        D3DReflect(program.byteCode, program.byteCodeLength, IID_ID3D12ShaderReflection, (void**)&reflector);
        D3D12_SHADER_DESC desc;
        reflector->GetDesc(&desc);

        for(unsigned int i = 0; i<desc.BoundResources; i++) {
            D3D12_SHADER_INPUT_BIND_DESC bindDesc;
            reflector->GetResourceBindingDesc(i, &bindDesc);

            switch(bindDesc.Type) {
                case D3D_SIT_CBUFFER:
                    {
                        ID3D12ShaderReflectionConstantBuffer *constantBuffer = reflector->GetConstantBufferByName(bindDesc.Name);
                        D3D12_SHADER_BUFFER_DESC bufferDesc;
                        constantBuffer->GetDesc(&bufferDesc);
                        ConstantBuffer *cb = ghnew ConstantBuffer(graphics, constantBuffer, bufferDesc, bindDesc.BindPoint, program.type.getVisibility());
                        cb->initParameters(parameterManager);
                        constantBuffers.add(cb);
                    }
                    break;
                case D3D_SIT_TBUFFER:
                    {
                        ID3D12ShaderReflectionConstantBuffer *constantBuffer = reflector->GetConstantBufferByName(bindDesc.Name);
                        D3D12_SHADER_BUFFER_DESC bufferDesc;
                        constantBuffer->GetDesc(&bufferDesc);
                        textureBuffers.add(ghnew TextureBufferConstant(constantBuffer, bufferDesc, bindDesc.BindPoint, program.type.getVisibility()));
                    }
                    break;
                case D3D_SIT_TEXTURE:
                    textures.add(ghnew TextureConstant(bindDesc.Name, bindDesc.BindPoint, program.type.getVisibility()));
                    break;
                case D3D_SIT_SAMPLER:
                    samplers.add(ghnew Sampler(bindDesc.Name, bindDesc.BindPoint, program.type.getVisibility()));
                    break;
            }
        }

        reflector->Release();
    }

    Status Shader::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags) {
        Status result;
        MemoryInputStream stream(data);

        if(stream.readBoolean()) {
            ShaderType types[] = {ShaderType::VS, ShaderType::PS, ShaderType::GS, ShaderType::HS, ShaderType::DS, ShaderType::CS};
            CompilationTarget targets[] = {CompilationTarget::SHADER_5_0};
            for(size_t i = 0; i<6; i++) {
                if(stream.readBoolean()) {
                    char *entryPoint = stream.readASCII();
                    CompilationTarget target = targets[stream.readInt()];
                    programs[i] = ghnew ShaderProgram(types[i], entryPoint, target);
                    size_t length = stream.readUInt();
                    programs[i]->byteCodeLength = length;
                    void *byteCode = ghnew BYTE[length];
                    memcpy(byteCode, stream.readBytes(length), length);
                    programs[i]->byteCode = byteCode;
                }
            }
            Graphics &graphics = resourceManager.Graphics;
            initConstants(graphics, resourceManager.ParameterManager);
            if((result = makeRootSignature(graphics))!=Status::OK)
                return result;
            if((result = makePipelineState(graphics))!=Status::OK)
                return result;
        }

        if(stream.readBoolean())
            source = copyStrA(stream.readASCII());

        return Status::OK;
    }

    Status Shader::saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags) const {
        MemoryOutputStream stream(data);

        stream.writeBoolean(compiled);
        if(compiled) {
            CompilationTarget targets[] = {CompilationTarget::SHADER_5_0};
            for(size_t i = 0; i<6; i++) {
                stream.writeBoolean(programs[i]!=nullptr);
                if(programs[i]!=nullptr) {
                    stream.writeASCII(programs[i]->getEntryPoint());
                    for(size_t j = 0; j<1; j++)
                        if(programs[i]->getCompilationTarget()==targets[j])
                            stream.writeInt(j);
                    stream.writeUInt(programs[i]->byteCodeLength);
                    stream.writeBytes(programs[i]->byteCode, programs[i]->byteCodeLength);
                }
            }
        }
        stream.writeBoolean(source!=nullptr);
        if(source!=nullptr)
            stream.writeASCII(source);

        *size = stream.getBytesWritten();

        return Status::OK;
    }

}