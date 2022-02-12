#pragma once

#include "core/resource/Resource.h"
#include "core/string/String.h"

#include "angelscript.h"

namespace Ghurund::Core {
    class ResourceManager;
    class ResourceContext;
}

namespace Ghurund {
    using namespace Ghurund::Core;

    class ScriptEngine;

    class Script:public Resource {
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
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

        static const Ghurund::Core::Type& GET_TYPE();

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

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"script", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}