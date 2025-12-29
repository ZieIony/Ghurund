#include "ghedxpch.h"
#include "DxShader.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/parameter/ValueParameter.h"
#include "variables/ConstantBuffer.h"
#include "variables/Sampler.h"
#include "variables/TextureConstant.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxShader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxShader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void DxShader::finalize() {
		if (rootSignature != nullptr)
			rootSignature->Release();
		if (pipelineState != nullptr)
			pipelineState->Release();

		constantBuffers.deleteItems();
		textures.deleteItems();
		samplers.deleteItems();
	}

	InputType DxShader::makeInputByType(
		D3D_SHADER_VARIABLE_CLASS _class,
		D3D_SHADER_VARIABLE_TYPE type,
		const AString& name,
		uint16_t size
	) {
		if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_SCALAR) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == IntParameter::SIZE)
					return InputType::INT;
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == FloatParameter::SIZE)
					return InputType::FLOAT;
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_VECTOR) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == Int2Parameter::SIZE)
					return InputType::INT2;
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == Float2Parameter::SIZE) {
					return InputType::FLOAT2;
				} else if (size == Float3Parameter::SIZE) {
					return InputType::FLOAT3;
				} else if (size == Float4Parameter::SIZE) {
					return InputType::FLOAT4;
				}
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_ROWS) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == MatrixParameter::SIZE) {
					return InputType::MATRIX;
				}
			}
		}
		auto message = std::format(
			_T("format [class: {}, type: {}, size: {}] of parameter '{}' is not supported\n"),
			(uint32_t)_class, (uint32_t)type, size, name
		);
		Logger::log(LogType::WARNING, message.c_str());
		AString exMessage = convertText<tchar, char>(String(message.c_str()));
		throw NotSupportedException(exMessage.Data);
	}

	void DxShader::applyInputs(CommandList& commandList) {
		size_t vi = 0;
		for (auto& cb : constantBuffers) {
			for (auto& v : cb->Variables) {
				auto& input = valueInputs[vi];
				auto value = input.value ? input.value : v.defaultValue;
				if (value)
					cb->setValue(value, v.size, v.offset);
				vi++;
			}
			cb->set(commandList);
		}

		for (size_t i = 0; i < textures.Size; i++) {
			DxTexture* texture = (DxTexture*)textureInputs[i].Value;
			if (!texture) {
				auto text = std::format(_T("Parameter for variable '{}' is missing.\n"), textures[i]->Name);
				Logger::logOnce(LogType::WARNING, text.c_str(), i);
				continue;
			}
			texture->set(commandList, textures[i]->BindSlot);
		}
	}

	void DxShader::init(
		const Array<VertexRole>& layout,
		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
		const List<ConstantBuffer*>& constantBuffers,
		const List<TextureConstant*>& textures,
		const List<Sampler*>& samplers,
		bool isTransparencyEnabled
	) {
		this->layout = layout;
		this->rootSignature = rootSignature.reset();
		this->pipelineState = pipelineState.reset();
		this->constantBuffers = constantBuffers;
		for (auto& cb : constantBuffers) {
			for (auto& v : cb->Variables) {
				InputType type = makeInputByType(
					v.variableClass,
					v.variableType,
					v.name,
					v.size
				);
				valueInputs.add(ValueInput(v.name, type, v.size, v.offset, v.defaultValue));
			}
		}
		this->textures = textures;
		for (auto& t : textures)
			textureInputs.add(TextureInput(t->Name));
		this->samplers = samplers;
		this->isTransparencyEnabled = isTransparencyEnabled;
	}

	bool DxShader::set(CommandList& commandList) {
		bool rsChanged = commandList.setGraphicsRootSignature(rootSignature);
		bool psChanged = commandList.setPipelineState(pipelineState);

		applyInputs(commandList);

		return rsChanged || psChanged;
	}

	DxShader::~DxShader() {
		finalize();
	}

	void DxShader::invalidate() {
		finalize();

		rootSignature = nullptr;
		pipelineState = nullptr;

		__super::invalidate();
	}
}