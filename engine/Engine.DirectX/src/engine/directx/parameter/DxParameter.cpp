#include "ghedxpch.h"
#include "DxParameter.h"

#include "core/logging/Formatter.h"

#include <DirectXMath.h>
#include <format>

namespace Ghurund::Engine::DirectX {
	Parameter* makeDxParameterByType(
		D3D_SHADER_VARIABLE_CLASS _class,
		D3D_SHADER_VARIABLE_TYPE type,
		const AString& name,
		uint16_t size,
		void* defaultValue,
		ParameterManager& parameterManager
	) {
		if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_SCALAR) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == IntParameter::SIZE)
					return makeDxParameter<IntParameter>(name, defaultValue, parameterManager);
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == FloatParameter::SIZE)
					return makeDxParameter<FloatParameter>(name, defaultValue, parameterManager);
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_VECTOR) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == Int2Parameter::SIZE)
					return makeDxParameter<Int2Parameter>(name, defaultValue, parameterManager);
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == Float2Parameter::SIZE) {
					return makeDxParameter<Float2Parameter>(name, defaultValue, parameterManager);
				} else if (size == Float3Parameter::SIZE) {
					return makeDxParameter<Float3Parameter>(name, defaultValue, parameterManager);
				} else if (size == Float4Parameter::SIZE) {
					return makeDxParameter<Float4Parameter>(name, defaultValue, parameterManager);
				}
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_ROWS) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == MatrixParameter::SIZE) {
					return makeDxParameter<MatrixParameter>(name, defaultValue, parameterManager);
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
}