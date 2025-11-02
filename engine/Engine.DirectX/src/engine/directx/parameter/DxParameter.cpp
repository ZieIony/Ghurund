#include "ghedxpch.h"
#include "DxParameter.h"

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
				if (size == sizeof(int32_t))
					return makeDxParameter<int32_t>(name, defaultValue, parameterManager);
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == sizeof(float))
					return makeDxParameter<float>(name, defaultValue, parameterManager);
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_VECTOR) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_INT) {
				if (size == sizeof(XMINT2))
					return makeDxParameter<XMINT2>(name, defaultValue, parameterManager);
			} else if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == sizeof(XMFLOAT2)) {
					return makeDxParameter<XMFLOAT2>(name, defaultValue, parameterManager);
				} else if (size == sizeof(XMFLOAT3)) {
					return makeDxParameter<XMFLOAT3>(name, defaultValue, parameterManager);
				} else if (size == sizeof(XMFLOAT4)) {
					return makeDxParameter<XMFLOAT4>(name, defaultValue, parameterManager);
				}
			}
		} else if (_class == D3D_SHADER_VARIABLE_CLASS::D3D10_SVC_MATRIX_ROWS) {
			if (type == D3D_SHADER_VARIABLE_TYPE::D3D10_SVT_FLOAT) {
				if (size == sizeof(XMFLOAT4X4)) {
					return makeDxParameter<XMFLOAT4X4>(name, defaultValue, parameterManager);
				}
			}
		}
		auto message = std::format(
			_T("format [class: {}, type: {}, size: {}] of parameter '{}' is not supported\n"),
			_class, type, size, name
		);
		Logger::log(LogType::WARNING, message.c_str());
		AString exMessage = convertText<tchar, char>(String(message.c_str()));
		throw NotSupportedException(exMessage.Data);
	}
}