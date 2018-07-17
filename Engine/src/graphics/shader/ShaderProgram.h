#pragma once

#include "ShaderType.h"
#include "CompilationTarget.h"

namespace Ghurund {
	class ShaderProgram {
	private:
		void *byteCode = nullptr;
		unsigned int byteCodeLength;
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

		ShaderProgram(const ShaderType &type, const void *byteCode, unsigned int length, const char *entryPoint = nullptr, CompilationTarget target = CompilationTarget::SHADER_5_0) : type(type), target(target) {
			this->byteCode = ghnew BYTE[length];
			memcpy(this->byteCode, byteCode, length);
            byteCodeLength = length;
			setEntryPoint(entryPoint);
		}

		~ShaderProgram() {
			delete[] byteCode;
			delete[] entryPoint;
		}

		Status compile(const char *code, char **outErrorMessages);

		void setEntryPoint(const char *entryPoint) {
			if (entryPoint == nullptr) {
				safeCopyStrA(&this->entryPoint, type.getEntryPoint());
			} else {
				safeCopyStrA(&this->entryPoint, entryPoint);
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

		void *getByteCode() {
			return byteCode;
		}

		unsigned int getByteCodeLength() {
			return byteCodeLength;
		}

		D3D12_INPUT_LAYOUT_DESC getInputLayout();

		ShaderType &getType() {
			return type;
		}

	};

}