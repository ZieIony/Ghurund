#pragma once

#include "resource/Resource.h"
#include "ScriptEngine.h"
#include "Argument.h"

namespace Ghurund {
    class Script:public Resource {
    private:
        asIScriptModule* mod = nullptr;
        asIScriptContext* ctx = nullptr;
        asIScriptFunction* func = nullptr;
        char* source = nullptr;
        char* entryPoint = nullptr;
        Array<Argument> arguments;

        void finalize() {
            safeDeleteArray(source);
            safeDeleteArray(entryPoint);
            mod = nullptr;
            func = nullptr; // no need to release
            if (ctx) {
                ctx->Release();
                ctx = nullptr;
            }
        }

    protected:
        virtual Status loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);

        virtual Status saveInternal(ResourceManager& resourceManager, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:
        Script():arguments(Array<Argument>(0)) {
            EntryPoint = "void main()";
        }

        ~Script() {
            finalize();
        }

        Status build(ScriptEngine& engine);

        virtual void invalidate() override {
            finalize();
            __super::invalidate();
        }

        void setSourceCode(const char* source) {
            safeCopyStr(&this->source, source);
        }

        const char* getSourceCode() {
            return source;
        }

        __declspec(property(get = getSourceCode, put = setSourceCode)) const char* SourceCode;

        void setEntryPoint(const char* entryPoint) {
            safeCopyStr(&this->entryPoint, entryPoint);
        }

        const char* getEntryPoint()const {
            return entryPoint;
        }

        __declspec(property(get = getEntryPoint, put = setEntryPoint)) const char* EntryPoint;

        void setArguments(const Array<Argument>& arguments) {
            this->arguments = arguments;
        }

        __declspec(property(put = setArguments)) const Array<Argument>& Arguments;

        void execute() {
            ctx->Prepare(func);
            for (size_t i = 0; i < arguments.Size; i++)
                arguments[i].set(i, *ctx);
            int r = ctx->Execute();
            if (r != asEXECUTION_FINISHED) {
                if (r == asEXECUTION_EXCEPTION)
                    Logger::log(LogType::ERR0R, _T("An exception '%hs' occurred. Please correct the code and try again.\n"), ctx->GetExceptionString());
            }
        }

        virtual const Ghurund::Type& getType() const override {
            return Type::SCRIPT;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::SCRIPT};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> & Formats;
    };
}