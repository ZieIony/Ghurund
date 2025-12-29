#include "ghedxpch.h"
#include "DxShaderCompiler.h"

#include "DxCompilationException.h"
#include "DxShaderProgram.h"

#include "core/Finally.h"
#include "engine/directx/DxGraphics.h"

#pragma warning(push, 0)
#include <d3dcompiler.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Microsoft::WRL;

	D3D12_INPUT_LAYOUT_DESC DxShaderCompiler::getInputLayout(const Buffer& byteCode) {
		ID3D12ShaderReflection* reflector = nullptr;
		D3DReflect(byteCode.Data, byteCode.Size, IID_ID3D12ShaderReflection, (void**)&reflector);
		D3D12_SHADER_DESC desc;
		reflector->GetDesc(&desc);

		D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;
		inputLayoutDesc.NumElements = desc.InputParameters;
		D3D12_INPUT_ELEMENT_DESC* inputElements = ghnew D3D12_INPUT_ELEMENT_DESC[desc.InputParameters];
		for (unsigned int i = 0; i < desc.InputParameters; i++) {
			D3D12_SIGNATURE_PARAMETER_DESC parameterDesc;
			reflector->GetInputParameterDesc(i, &parameterDesc);
			inputElements[i].SemanticName = copyStr(parameterDesc.SemanticName);
			inputElements[i].SemanticIndex = parameterDesc.SemanticIndex;
			inputElements[i].Format = getFormat(parameterDesc.Mask, parameterDesc.ComponentType);
			inputElements[i].InputSlot = i;
			inputElements[i].AlignedByteOffset = 0;
			inputElements[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			inputElements[i].InstanceDataStepRate = 0;
		}
		inputLayoutDesc.pInputElementDescs = inputElements;

		reflector->Release();

		return inputLayoutDesc;
	}

	Array<VertexRole> DxShaderCompiler::makeLayout(const D3D12_INPUT_LAYOUT_DESC& desc) {
		Array<VertexRole> layout(desc.NumElements);
		for (size_t i = 0; i < desc.NumElements; i++) {
			auto& inputElement = desc.pInputElementDescs[i];
			if (AString("POSITION") == inputElement.SemanticName) {
				layout[i] = VertexRole::POSITION;
			} else if (AString("TEXCOORD") == inputElement.SemanticName) {
				layout[i] = VertexRole::TEXCOORD;
			} else if (AString("NORMAL") == inputElement.SemanticName) {
				layout[i] = VertexRole::NORMAL;
			}
		}
		return layout;
	}

	DXGI_FORMAT DxShaderCompiler::getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType) {
		if (mask == 1) {
			if (componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32_UINT;
			else if (componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32_SINT;
			else if (componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32_FLOAT;
		} else if (mask <= 3) {
			if (componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32_UINT;
			else if (componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32_SINT;
			else if (componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32_FLOAT;
		} else if (mask <= 7) {
			if (componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32_UINT;
			else if (componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32_SINT;
			else if (componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32_FLOAT;
		} else if (mask <= 15) {
			if (componentType == D3D_REGISTER_COMPONENT_UINT32) return DXGI_FORMAT_R32G32B32A32_UINT;
			else if (componentType == D3D_REGISTER_COMPONENT_SINT32) return DXGI_FORMAT_R32G32B32A32_SINT;
			else if (componentType == D3D_REGISTER_COMPONENT_FLOAT32) return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

	DxShaderProgram* DxShaderCompiler::compile(const AString& sourceCode, const DxShaderType& shaderType, CompilerInclude* include, bool debug) {
		unsigned int compileFlags = debug ? D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION : 0;

		ID3DBlob* errorBlob;
		ComPtr<ID3DBlob> shader;
		AString entryPoint = shaderType.getEntryPoint();
		AString target = makeCompilationTarget(shaderType);
		HRESULT hr = D3DCompile(sourceCode.Data, sourceCode.Length, nullptr, nullptr, include, entryPoint.Data, target.Data, compileFlags, 0, &shader, &errorBlob);
		if (FAILED(hr)) {
			if (errorBlob == nullptr) {
				Logger::log(LogType::ERR0R, _T("Unknown error while compiling shader\n"));
				throw DxCompilationException(hr, "Unknown error while compiling shader");
			} else {
				AString errorMessages((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
				errorBlob->Release();
				if (errorMessages.contains("entrypoint not found")) {
					return nullptr;
				} else {
					auto text = std::format(_T("Error while compiling shader:\n%s\n"), errorMessages);
					Logger::log(LogType::ERR0R, text.c_str());
					throw DxCompilationException(hr, errorMessages.Data);
				}
			}
		} else {
			auto sourceCode = Buffer(shader->GetBufferPointer(), shader->GetBufferSize());
			return ghnew DxShaderProgram(shaderType, sourceCode, entryPoint);
		}
	}

	OwnedNotNull<DxShader, RefCountedObjectDeleter> DxShaderCompiler::build(
		const Array<SharedPointer<DxShaderProgram>>& programs,
		ShaderSettings shaderSettings
	) {
		List<ConstantBuffer*> constantBuffers;
		List<TextureConstant*> textures;
		List<Sampler*> samplers;
		for (auto& program : programs)
			initConstants(*program.get(), constantBuffers, textures, samplers);

		D3D12_INPUT_LAYOUT_DESC inputLayout;
		for (auto& program : programs) {
			if (program->Type == DxShaderType::VERTEX) {
				inputLayout = getInputLayout(program->ByteCode);
				break;
			}
		}
		Array<VertexRole> layout = makeLayout(inputLayout);
		Finally f = [&] {
			for (size_t i = 0; i < inputLayout.NumElements; i++)
				delete[] inputLayout.pInputElementDescs[i].SemanticName;
			delete[] inputLayout.pInputElementDescs;
		};

		auto rootSignature = makeRootSignature(constantBuffers, textures, samplers);
		auto pipelineState = makePipelineState(programs, inputLayout, &rootSignature, shaderSettings);
		OwnedNotNull<DxShader, RefCountedObjectDeleter> shader(ghnew DxShader());
		shader->init(
			layout,
			std::move(rootSignature),
			std::move(pipelineState),
			constantBuffers,
			textures,
			samplers,
			shaderSettings.isTransparencyEnabled
		);
		return shader;
	}

	OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> DxShaderCompiler::makePipelineState(
		const Array<SharedPointer<DxShaderProgram>>& programs,
		D3D12_INPUT_LAYOUT_DESC inputLayout,
		ID3D12RootSignature* rootSignature,
		ShaderSettings shaderSettings
	) {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.DepthStencilState.DepthEnable = shaderSettings.isDepthTestEnabled;
		psoDesc.pRootSignature = rootSignature;
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.RasterizerState.CullMode = shaderSettings.cullMode;

		for (auto& program : programs) {
			if (program->Type == DxShaderType::VERTEX) {
				psoDesc.InputLayout = inputLayout;
				psoDesc.VS.pShaderBytecode = program->ByteCode.Data;
				psoDesc.VS.BytecodeLength = program->ByteCode.Size;
			} else if (program->Type == DxShaderType::PIXEL) {
				psoDesc.PS.pShaderBytecode = program->ByteCode.Data;
				psoDesc.PS.BytecodeLength = program->ByteCode.Size;
			} else if (program->Type == DxShaderType::GEOMETRY) {
				psoDesc.GS.pShaderBytecode = program->ByteCode.Data;
				psoDesc.GS.BytecodeLength = program->ByteCode.Size;
			} else if (program->Type == DxShaderType::HULL) {
				psoDesc.HS.pShaderBytecode = program->ByteCode.Data;
				psoDesc.HS.BytecodeLength = program->ByteCode.Size;
			} else if (program->Type == DxShaderType::D0MAIN) {
				psoDesc.DS.pShaderBytecode = program->ByteCode.Data;
				psoDesc.DS.BytecodeLength = program->ByteCode.Size;
			}
		}

		if (psoDesc.VS.BytecodeLength == 0) {
			Logger::log(LogType::ERR0R, _T("Vertex shader program is required.\n"));
			throw InvalidStateException("Vertex shader program is required.");
		}
		if (psoDesc.PS.BytecodeLength == 0) {
			Logger::log(LogType::ERR0R, _T("Pixel shader program is required.\n"));
			throw InvalidStateException("Pixel shader program is required.");
		}

		if (shaderSettings.isTransparencyEnabled) {
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

		ID3D12PipelineState* pipelineState = nullptr;
		if (FAILED(graphics.Device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateGraphicsPipelineState() failed\n"));
			throw CallFailedException();
		}

		return OwnedNotNull<ID3D12PipelineState, IUnknownDeleter>(pipelineState);
	}

	OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> DxShaderCompiler::makeRootSignature(
		const List<ConstantBuffer*>& constantBuffers,
		const List<TextureConstant*>& textures,
		const List<Sampler*>& samplers
	) {
		size_t paramCount = constantBuffers.Size + textures.Size;
		Array<CD3DX12_ROOT_PARAMETER1> rootParameters(paramCount);

		unsigned int r = 0;
		for (size_t i = 0; i < constantBuffers.Size; i++, r++) {
			ShaderConstant* constant = constantBuffers.get(i);
			constant->BindSlot = r;
			rootParameters[r].InitAsConstantBufferView(constant->getBindPoint(), 0, D3D12_ROOT_DESCRIPTOR_FLAG_NONE, constant->getVisibility());
		}

		Array<CD3DX12_DESCRIPTOR_RANGE1> ranges(textures.Size);
		for (size_t i = 0; i < textures.Size; i++, r++) {
			ShaderConstant* constant = textures.get(i);
			constant->BindSlot = r;
			ranges[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, constant->getBindPoint(), 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
			rootParameters[r].InitAsDescriptorTable(1, &ranges[i], constant->getVisibility());
		}

		Array<D3D12_STATIC_SAMPLER_DESC> samplerDescs(samplers.Size);
		for (size_t i = 0; i < samplers.Size; i++) {
			samplers[i]->build();
			samplerDescs[i] = samplers.get(i)->samplerDesc;
		}

		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Init_1_1(
			(UINT)paramCount,
			&rootParameters[0],
			(UINT)samplers.Size,
			&samplerDescs[0],
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		if (FAILED(D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error))) {
			auto text = std::format(_T("D3D12SerializeRootSignature() failed\n%hs"), error->GetBufferPointer());
			Logger::log(LogType::ERR0R, text.c_str());
			throw CallFailedException();
		}
		ID3D12RootSignature* rootSignature = nullptr;
		if (FAILED(graphics.Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateRootSignature() failed\n"));
			throw CallFailedException();
		}
		return OwnedNotNull<ID3D12RootSignature, IUnknownDeleter>(rootSignature);
	}

	void DxShaderCompiler::initConstants(
		const DxShaderProgram& program,
		List<ConstantBuffer*>& constantBuffers,
		List<TextureConstant*>& textures,
		List<Sampler*>& samplers
	) {
		ID3D12ShaderReflection* reflector = nullptr;
		D3DReflect(program.ByteCode.Data, program.ByteCode.Size, IID_ID3D12ShaderReflection, (void**)&reflector);
		D3D12_SHADER_DESC desc;
		reflector->GetDesc(&desc);

		for (unsigned int i = 0; i < desc.BoundResources; i++) {
			D3D12_SHADER_INPUT_BIND_DESC bindDesc;
			reflector->GetResourceBindingDesc(i, &bindDesc);

			switch (bindDesc.Type) {
			case D3D_SIT_CBUFFER:
			{
				ID3D12ShaderReflectionConstantBuffer* constantBuffer = reflector->GetConstantBufferByName(bindDesc.Name);
				D3D12_SHADER_BUFFER_DESC bufferDesc;
				constantBuffer->GetDesc(&bufferDesc);
				ConstantBuffer* cb = [&] {
					for (size_t i = 0; i < constantBuffers.Size; i++) {
						if (strcmp(bindDesc.Name, constantBuffers[i]->Name.Data) == 0) {
							constantBuffers[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
							return constantBuffers[i];
						}
					}
					ConstantBuffer* cb = ghnew ConstantBuffer(bindDesc.Name, bindDesc.BindPoint, program.getType().getVisibility());
					cb->init(graphics, bufferDesc);
					constantBuffers.add(cb);
					return cb;
				}();
				cb->initVariables(constantBuffer, bufferDesc);
			}
			break;
			case D3D_SIT_TEXTURE:
				for (size_t i = 0; i < textures.Size; i++) {
					if (strcmp(bindDesc.Name, textures[i]->Name.Data) == 0) {
						textures[i]->Visibility = D3D12_SHADER_VISIBILITY_ALL;
						goto bufferMerged;
					}
				}
				textures.add(ghnew TextureConstant(bindDesc.Name, bindDesc.BindPoint, program.getType().getVisibility()));
				break;
			case D3D_SIT_SAMPLER:
				for (size_t i = 0; i < samplers.Size; i++) {
					if (strcmp(bindDesc.Name, samplers[i]->Name.Data) == 0) {
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
}
