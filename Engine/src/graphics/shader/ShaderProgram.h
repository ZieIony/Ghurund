#pragma once

#include "ShaderType.h"
#include "CompilationTarget.h"
#include "core/Buffer.h"

namespace Ghurund {
	class ShaderProgram {
	private:
		Buffer *byteCode = nullptr;
		char *entryPoint = nullptr;
		ShaderType type;
		CompilationTarget target;

		DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

		const char *makeCompilationTarget() {
			const char *targetText = target.toString();
			const char *typeText = type.toString();
			char *text = ghnew char[10];;
			sprintf_s(text, 10, "%s_%s", typeText, targetText);
			return text;
		}

	public:
		ShaderProgram(const ShaderType &type, const char *entryPoint = nullptr, const CompilationTarget &target = CompilationTarget::SHADER_5_0) : type(type), target(target) {
			setEntryPoint(entryPoint);
		}

		ShaderProgram(const ShaderType &type, Buffer &byteCode, const char *entryPoint = nullptr, CompilationTarget target = CompilationTarget::SHADER_5_0) : type(type), target(target) {
			this->byteCode = ghnew Buffer(byteCode);
			setEntryPoint(entryPoint);
		}

		~ShaderProgram() {
			delete byteCode;
			delete[] entryPoint;
		}

		Status compile(const char *code, char **outErrorMessages);

		void setEntryPoint(const char *entryPoint) {
			if (entryPoint == nullptr) {
				safeCopyStr(&this->entryPoint, type.getEntryPoint());
			} else {
				safeCopyStr(&this->entryPoint, entryPoint);
			}
		}

		const char *getEntryPoint()const {
			return entryPoint;
		}

		void setCompilationTarget(const CompilationTarget &target) {
			this->target = target;
		}

		const CompilationTarget &getCompilationTarget()const {
			return target;
		}

		Buffer *getByteCode() {
			return byteCode;
		}

        __declspec(property(get = getByteCode)) Buffer *ByteCode;

		D3D12_INPUT_LAYOUT_DESC getInputLayout();

		ShaderType &getType() {
			return type;
		}

	};

}