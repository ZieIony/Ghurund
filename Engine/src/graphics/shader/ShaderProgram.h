#pragma once

#include "ShaderType.h"
#include "CompilationTarget.h"
#include "core/Buffer.h"

namespace Ghurund {
    class ShaderProgram {
    private:
        Buffer* byteCode = nullptr;
        AString entryPoint;
        ShaderType type;
        CompilationTarget target;

        DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

        const char* makeCompilationTarget() {
            const char* targetText = target.toString();
            const char* typeText = type.toString();
            char* text = ghnew char[10];;
            sprintf_s(text, 10, "%s_%s", typeText, targetText);
            return text;
        }

    public:
        ShaderProgram(const ShaderType& type, const AString& entryPoint, const CompilationTarget& target = CompilationTarget::SHADER_5_0):
            type(type), entryPoint(entryPoint), target(target) {}

        ShaderProgram(const ShaderType& type, Buffer& byteCode, const AString& entryPoint, CompilationTarget target = CompilationTarget::SHADER_5_0)
            : type(type), entryPoint(entryPoint), target(target) {
            this->byteCode = ghnew Buffer(byteCode);
        }

        ~ShaderProgram() {
            delete byteCode;
        }

        Status compile(const char* code, char** outErrorMessages, const wchar_t* fileName = nullptr);

        void setEntryPoint(const AString& entryPoint) {
            this->entryPoint = entryPoint;
        }

        const AString& getEntryPoint()const {
            return entryPoint;
        }

        __declspec(property(get = getEntryPoint, put = setEntryPoint)) const AString& EntryPoint;

        void setCompilationTarget(const CompilationTarget& target) {
            this->target = target;
        }

        const CompilationTarget& getCompilationTarget()const {
            return target;
        }

        Buffer* getByteCode() {
            return byteCode;
        }

        __declspec(property(get = getByteCode)) Buffer* ByteCode;

        D3D12_INPUT_LAYOUT_DESC getInputLayout();

        ShaderType& getType() {
            return type;
        }

    };

}