#include "ghedxpch.h"
#include "BufferConstantField.h"

#include "engine/parameter/ValueParameter.h"

namespace Ghurund::Engine::DirectX {
	InputType BufferConstantField::makeInputType() const {
		if (variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_SCALAR) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == IntParameter::SIZE)
					return InputType::INT;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_UINT) {
				if (size == IntParameter::SIZE)
					return InputType::UINT;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_BOOL) {
				if (size == IntParameter::SIZE)
					return InputType::BOOL;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == FloatParameter::SIZE)
					return InputType::FLOAT;
			}
		} else if (variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_VECTOR) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == Int2Parameter::SIZE)
					return InputType::INT2;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == Float2Parameter::SIZE) {
					return InputType::FLOAT2;
				} else if (size == Float3Parameter::SIZE) {
					return InputType::FLOAT3;
				} else if (size == Float4Parameter::SIZE) {
					return InputType::FLOAT4;
				}
			}
		} else if (
			// HLSL prefers column-major matrices, so let's just not support row-major
			//_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_ROWS ||
			variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_COLUMNS
			) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == MatrixParameter::SIZE) {
					return InputType::MATRIX;
				}
			}
		}
		auto message = std::format(
			_T("format [class: {}, type: {}, size: {}] of parameter '{}' is not supported\n"),
			(uint32_t)variableClass, (uint32_t)variableType, size, name
		);
		Logger::log(LogType::WARNING, message.c_str());
		AString exMessage = convertText<tchar, char>(String(message.c_str()));
		throw NotSupportedException(exMessage.Data);
	}
}
