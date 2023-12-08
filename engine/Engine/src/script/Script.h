#pragma once

#include "core/resource/Resource.h"
#include "core/string/String.h"

#include "angelscript.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund {
    using namespace Ghurund::Core;

    class ScriptEngine;

    class Script:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Script::GET_TYPE();
#pragma endregion

    private:
		asIScriptModule* mod = nullptr;
        asIScriptContext* ctx = nullptr;
        asIScriptFunction* func = nullptr;
        AString source;
        AString entryPoint;
        Array<void*> arguments;
        bool built = false;

        void finalize() {
            source = nullptr;
            entryPoint = nullptr;
            mod = nullptr;
            func = nullptr; // no need to release
            if (ctx) {
                ctx->Release();
                ctx = nullptr;
            }
            built = false;
        }

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:
        Script():arguments(Array<void*>(0)) {
            EntryPoint = "void main()";
        }

        ~Script() {
            finalize();
        }

        Status build(ScriptEngine& engine);

        bool getIsBuilt() {
            return built;
        }

        __declspec(property(get = getIsBuilt)) bool IsBuilt;

        virtual void invalidate() override {
            finalize();
            __super::invalidate();
        }

        virtual bool isValid() const {
            return __super::isValid() && built;
        }

        void setSourceCode(const AString& source) {
            this->source = source;
            built = false;
        }

        const AString& getSourceCode() {
            return source;
        }

        __declspec(property(get = getSourceCode, put = setSourceCode)) const AString& SourceCode;

        void setEntryPoint(const AString& entryPoint) {
            this->entryPoint = entryPoint;
            built = false;
        }

        const AString& getEntryPoint()const {
            return entryPoint;
        }

        __declspec(property(get = getEntryPoint, put = setEntryPoint)) const AString& EntryPoint;

        void setArguments(const Array<void*>& arguments) {
            this->arguments = arguments;
        }

        __declspec(property(put = setArguments)) const Array<void*>& Arguments;

        Status execute();

        int getIntResult() {
            return ctx->GetReturnWord();
        }

        float getFloatResult() {
            return ctx->GetReturnFloat();
        }

        void *getObjectResult() {
            return ctx->GetReturnObject();
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"script", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}