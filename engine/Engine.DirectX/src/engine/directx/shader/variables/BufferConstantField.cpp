#include "ghedxpch.h"
#include "BufferConstantField.h"

#include "engine/parameter/ValueParameter.h"

namespace Ghurund::Engine::DirectX {
	ConstantType BufferConstantField::makeConstantType() const {
		if (variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_SCALAR) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == IntParameter::SIZE)
					return ConstantType::INT;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_UINT) {
				if (size == IntParameter::SIZE)
					return ConstantType::UINT;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_BOOL) {
				if (size == IntParameter::SIZE)
					return ConstantType::BOOL;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == FloatParameter::SIZE)
					return ConstantType::FLOAT;
			}
		} else if (variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_VECTOR) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == Int2Parameter::SIZE)
					return ConstantType::INT2;
			} else if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == Float2Parameter::SIZE) {
					return ConstantType::FLOAT2;
				} else if (size == Float3Parameter::SIZE) {
					return ConstantType::FLOAT3;
				} else if (size == Float4Parameter::SIZE) {
					return ConstantType::FLOAT4;
				}
			}
		} else if (
			// HLSL prefers column-major matrices, so let's just not support row-major
			//_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_ROWS ||
			variableClass == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_COLUMNS
			) {
			if (variableType == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == MatrixParameter::SIZE) {
					return ConstantType::MATRIX;
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
