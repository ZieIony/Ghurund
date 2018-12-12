#include "Shader.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    Status Shader::makeRootSignature() {
        Status result = Status::OK;

        size_t paramCount = constantBuffers.Size+textureBuffers.Size+textures.Size;
        CD3DX12_ROOT_PARAMETER1 *rootParameters = ghnew CD3DX12_ROOT_PARAMETER1[paramCount];
        CD3DX12_DESCRIPTOR_RANGE1 *ranges = ghnew CD3DX12_DESCRIPTOR_RANGE1[paramCount];

        unsigned int r = 0;
        for(size_t i = 0; i<constantBuffers.Size; i++, r++) {
            ShaderConstant *constant = constantBuffers.get(i);
            constant->BindSlot = r;
            ranges[r].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, constant->getBindPoint(), 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
            rootParameters[r].InitAsDescriptorTable(1, &ranges[r], constant->getVisibility());
        }

        for(size_t i = 0; i<textures.Size; i++, r++) {
            ShaderConstant *constant = textures.get(i);
            constant->BindSlot = r;
            ranges[r].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, constant->getBindPoint(), 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
            rootParameters[r].InitAsDescriptorTable(1, &ranges[r], constant->getVisibility());
        }

        D3D12_STATIC_SAMPLER_DESC *samplerDescs = ghnew D3D12_STATIC_SAMPLER_DESC[samplers.Size];
        for(size_t i = 0; i<samplers.Size; i++) {
            samplers[i]->build();
            samplerDescs[i] = samplers.get(i)->samplerDesc;
        }

        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init_1_1(paramCount,
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
        if(FAILED(graphics->Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)))) {
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

    Status Shader::makePipelineState(bool supportsTransparency) {
        if(pipelineState!=nullptr)
            pipelineState->Release();

        this->supportsTransparency = supportsTransparency;
        Status result = Status::OK;

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = getInputLayout();
        psoDesc.pRootSignature = rootSignature;

        ShaderType types[] = {ShaderType::VS, ShaderType::PS, ShaderType::GS, ShaderType::HS, ShaderType::DS, ShaderType::CS};
        if(programs[0]!=nullptr) {
            psoDesc.VS.pShaderBytecode = programs[0]->ByteCode->Data;
            psoDesc.VS.BytecodeLength = programs[0]->ByteCode->Size;
        }
        if(programs[1]!=nullptr) {
            psoDesc.PS.pShaderBytecode = programs[1]->ByteCode->Data;
            psoDesc.PS.BytecodeLength = programs[1]->ByteCode->Size;
        }
        if(programs[2]!=nullptr) {
            psoDesc.GS.pShaderBytecode = programs[2]->ByteCode->Data;
            psoDesc.GS.BytecodeLength = programs[2]->ByteCode->Size;
        }

        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

        if(supportsTransparency) {
            psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
            psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
            psoDesc.BlendState.RenderTarget[0].BlendEnable = true;
            psoDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
            psoDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
            psoDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
            psoDesc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
            psoDesc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;
            psoDesc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
            psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = 0x0F;
        } else {
            psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
            psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        }
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
        psoDesc.SampleDesc.Count = 1;
        if(FAILED(graphics->Device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)))) {
            Logger::log(_T("device->CreateGraphicsPipelineState() failed\n"));
            result = Status::CALL_FAIL;
        }

        for(unsigned int i = 0; i<psoDesc.InputLayout.NumElements; i++)
            delete[] psoDesc.InputLayout.pInputElementDescs[i].SemanticName;
        delete[] psoDesc.InputLayout.pInputElementDescs;

        return result;
    }

    void Shader::finalize() {
        if(rootSignature!=nullptr)
            rootSignature->Release();
        if(pipelineState!=nullptr)
            pipelineState->Release();

        constantBuffers.deleteItems();
        textureBuffers.deleteItems();
        textures.deleteItems();
        samplers.deleteItems();
        for(size_t i = 0; i<6; i++)
            delete programs[i];
        delete[] source;

        delete parameters;
    }

    Shader::~Shader() {
        finalize();
    }

    void Shader::invalidate() {
        finalize();

        rootSignature = nullptr;
        pipelineState = nullptr;

        for(size_t i = 0; i<6; i++)
            programs[i] = nullptr;

        source = nullptr;
        parameters = nullptr;

        __super::invalidate();
    }

    Status Shader::compile(char **outErrorMessages) {
        ShaderType types[] = {ShaderType::VS, ShaderType::PS, ShaderType::GS, ShaderType::HS, ShaderType::DS, ShaderType::CS};
        ASCIIString output;
        Status result = Status::OK;
        for(unsigned int i = 0; i<6; i++) {
            ShaderProgram *program = ghnew ShaderProgram(types[i]);
            char *programErrors = nullptr;
            result = program->compile(source, &programErrors);
            if(result==Status::OK) {
                programs[i] = program;
            } else if(result==Status::ENTRY_POINT_NOT_FOUND) {
                output.add("'");
                output.add(types[i].getEntryPoint());
                output.add("' not found\n");
                delete program;
                result = Status::OK;
            } else {
                if(programErrors!=nullptr) {
                    output.add(programErrors);
                    delete[] programErrors;
                }
                delete program;
            }
        }
        if(output.Length>0&&outErrorMessages!=nullptr)
            *outErrorMessages = copyStrA(output.getData());
        compiled = result == Status::OK;
        return result;
    }

    Status Shader::build(ResourceContext & context, bool supportsTransparency, char ** output) {
        Status result;
        if(!compiled)
            if((result = compile(output))!=Status::OK)
                return result;
        Graphics &graphics = context.Graphics;
        initConstants(context.ParameterManager);
        if((result = makeRootSignature())!=Status::OK)
            return result;
        return makePipelineState(supportsTransparency);
    }

    void Shader::initParameters(ParameterManager & parameterManager) {
        if(parameters!=nullptr)
            return;

        size_t paramCount = 0;
        for(size_t i = 0; i<constantBuffers.Size; i++) {
            constantBuffers[i]->initParameters(parameterManager);
            paramCount += constantBuffers[i]->Parameters.Size;
        }
        parameters = ghnew Array<Parameter*>(paramCount+textureBuffers.Size+textures.Size);    // TODO: correct number of parameters
        size_t paramOffset = 0;
        for(size_t i = 0; i<constantBuffers.Size; i++) {
            constantBuffers[i]->Parameters.copyTo(*parameters, paramOffset);
            paramOffset += constantBuffers[i]->Parameters.Size;
        }
    }

    D3D12_INPUT_LAYOUT_DESC Shader::getInputLayout() {
        return programs[0]->getInputLayout();
    }

    void Shader::initConstants(ParameterManager &parameterManager) {
        for(unsigned int i = 0; i<6; i++)
            if(programs[i]!=nullptr)
                initConstants(parameterManager, *programs[i]);
    }

    void Shader::initConstants(ParameterManager &parameterManager, ShaderProgram &program) {
        ID3D12ShaderReflection* reflector = nullptr;
        D3DReflect(program.ByteCode->Data, program.ByteCode->Size, IID_ID3D12ShaderReflection, (void**)&reflector);
        D3D12_SHADER_DESC desc;
        reflector->GetDesc(&desc);

        for(unsigned int i = 0; i<desc.BoundResources; i++) {
            D3D12_SHADER_INPUT_BIND_DESC bindDesc;
            reflector->GetResourceBindingDesc(i, &bindDesc);

            switch(bindDesc.Type) {
                case D3D_SIT_CBUFFER:
                    {
                        for(size_t i = 0; i<constantBuffers.Size; i++) {
                            if(strcmp(bindDesc.Name, constantBuffers[i]->getName())==0) {
                                constantBuffers[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
                                goto bufferMerged;
                            }
                        }
                        ID3D12ShaderReflectionConstantBuffer *constantBuffer = reflector->GetConstantBufferByName(bindDesc.Name);
                        D3D12_SHADER_BUFFER_DESC bufferDesc;
                        constantBuffer->GetDesc(&bufferDesc);
                        ConstantBuffer *cb = ghnew ConstantBuffer(*graphics, constantBuffer, bufferDesc, bindDesc.BindPoint, program.getType().getVisibility());
                        constantBuffers.add(cb);
                    }
                    break;
                case D3D_SIT_TBUFFER:
                    {
                        for(size_t i = 0; i<textureBuffers.Size; i++) {
                            if(strcmp(bindDesc.Name, textureBuffers[i]->getName())==0) {
                                textureBuffers[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
                                goto bufferMerged;
                            }
                        }
                        ID3D12ShaderReflectionConstantBuffer *constantBuffer = reflector->GetConstantBufferByName(bindDesc.Name);
                        D3D12_SHADER_BUFFER_DESC bufferDesc;
                        constantBuffer->GetDesc(&bufferDesc);
                        textureBuffers.add(ghnew TextureBufferConstant(constantBuffer, bufferDesc, bindDesc.BindPoint, program.getType().getVisibility()));
                    }
                    break;
                case D3D_SIT_TEXTURE:
                    for(size_t i = 0; i<textures.Size; i++) {
                        if(strcmp(bindDesc.Name, textures[i]->getName())==0) {
                            textures[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
                            goto bufferMerged;
                        }
                    }
                    textures.add(ghnew TextureConstant(bindDesc.Name, bindDesc.BindPoint, program.getType().getVisibility()));
                    break;
                case D3D_SIT_SAMPLER:
                    for(size_t i = 0; i<samplers.Size; i++) {
                        if(strcmp(bindDesc.Name, samplers[i]->getName())==0) {
                            samplers[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
                            goto bufferMerged;
                        }
                    }
                    samplers.add(ghnew Sampler(bindDesc.Name, bindDesc.BindPoint, program.getType().getVisibility()));
                    break;
            }

        bufferMerged:;
        }

        reflector->Release();
    }

    Status Shader::loadShd(ResourceContext &context, MemoryInputStream &stream) {
        Status result;

        result = readHeader(stream);
        if(result!=Status::OK)
            return result;

        if(stream.readBoolean()) {
            for(size_t i = 0; i<6; i++) {
                if(stream.readBoolean()) {
                    char *entryPoint = stream.readASCII();
                    const CompilationTarget &target = CompilationTarget::fromValue(stream.readInt());
                    unsigned int length = stream.readUInt();
                    programs[i] = ghnew ShaderProgram(ShaderType::values[i], Buffer(stream.readBytes(length), length), entryPoint, target);
                }
            }
        }

        if(stream.readBoolean())
            source = copyStrA(stream.readASCII());

        supportsTransparency = stream.readBoolean();
        Graphics &graphics = context.Graphics;
        initConstants(context.ParameterManager);
        if((result = makeRootSignature())!=Status::OK)
            return result;
        if((result = makePipelineState(supportsTransparency))!=Status::OK)
            return result;

        return Status::OK;
    }

    Status Shader::loadHlsl(ResourceContext &context, MemoryInputStream &stream) {
        ASCIIString sourceCode((const char *)stream.Data, stream.Size);
        setSourceCode(sourceCode.getData());

        this->graphics = &context.Graphics;

        return build(context);
    }

    Status Shader::loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
        this->graphics = &context.Graphics;
        Status result;

        if(!FileName.Empty) {
            if(FileName.endsWith(ResourceFormat::SHADER.getExtension())) {
                result = loadShd(context, stream);
            } else if(FileName.endsWith(ResourceFormat::HLSL.getExtension())) {
                result = loadHlsl(context, stream);
            } else {
                return Status::UNKNOWN_FORMAT;
            }
        } else {
            size_t bytesRead = stream.BytesRead;
            result = loadShd(context, stream);
            if(result!=Status::OK) {
                stream.set(bytesRead);
                result = loadHlsl(context, stream);
                if(result!=Status::OK)
                    return Status::UNKNOWN_FORMAT;
            }
        }

        if(result==Status::OK)
            initParameters(context.ParameterManager);

        return result;
    }

    Status Shader::saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
        writeHeader(stream);

        stream.writeBoolean(compiled);
        if(compiled) {
            for(size_t i = 0; i<6; i++) {
                stream.writeBoolean(programs[i]!=nullptr);
                if(programs[i]!=nullptr) {
                    stream.writeASCII(programs[i]->getEntryPoint());
                    stream.writeInt(programs[i]->getCompilationTarget().getValue());
                    stream.writeUInt(programs[i]->ByteCode->Size);
                    stream.writeBytes(programs[i]->ByteCode->Data, programs[i]->ByteCode->Size);
                }
            }
        }
        stream.writeBoolean(source!=nullptr);
        if(source!=nullptr)
            stream.writeASCII(source);

        stream.writeBoolean(supportsTransparency);

        return Status::OK;
    }

}