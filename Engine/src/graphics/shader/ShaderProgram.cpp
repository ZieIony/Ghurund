#include "ShaderProgram.h"

namespace Ghurund {
    Status ShaderProgram::compile(const char *code, char **outErrorMessages) {
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
        HRESULT hr = D3DCompile(code, strlen(code), nullptr, nullptr, nullptr, entryPoint, targetText, compileFlags, 0, &shader, &errorBlob);
        if(FAILED(hr)) {
            if(errorBlob == nullptr) {
                Logger::log(_T("Unknown error while compiling shader\n"));
                result = Status::COMPILATION_ERROR;
            } else {
                ASCIIString errorMessages((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
                if(errorMessages.find("error X3501")<errorBlob->GetBufferSize()) {
                    result = Status::ENTRY_POINT_NOT_FOUND;
                } else {
                    Logger::log(_T("Error while compiling shader:\n%hs\n"), errorMessages.getData());
                    result = Status::COMPILATION_ERROR;
                    if(outErrorMessages != nullptr) {
                        *outErrorMessages = ghnew char[errorBlob->GetBufferSize()];
                        memcpy(*outErrorMessages, errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
                    }
                }
                errorBlob->Release();
            }
        } else {
            byteCode = ghnew Buffer(shader->GetBufferPointer(), shader->GetBufferSize());
            result = Status::OK;
        }

        delete[] targetText;
        return result;
    }

    D3D12_INPUT_LAYOUT_DESC ShaderProgram::getInputLayout() {
        ID3D12ShaderReflection* reflector = nullptr;
        D3DReflect(byteCode->Data, byteCode->Size, IID_ID3D12ShaderReflection, (void**)&reflector);
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
            inputElements[i].AlignedByteOffset = i == 0 ? 0 : D3D12_APPEND_ALIGNED_ELEMENT;
            inputElements[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
        }
        inputLayoutDesc.pInputElementDescs = inputElements;

        reflector->Release();

        return inputLayoutDesc;
    }

    DXGI_FORMAT ShaderProgram::getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType) {
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
}