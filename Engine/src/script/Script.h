#pragma once

#include "Argument.h"

#include "resource/Resource.h"

namespace Ghurund {
    class ScriptEngine;
    class ResourceManager;
    class ResourceContext;

    class Script:public Resource {
    private:
		asIScriptModule* mod = nullptr;
        asIScriptContext* ctx = nullptr;
        asIScriptFunction* func = nullptr;
        char* source = nullptr;
        char* entryPoint = nullptr;
        Array<Argument> arguments;
        bool built = false;

        void finalize() {
            delete[] source;
            source = nullptr;
            delete[] entryPoint;
            entryPoint = nullptr;
            mod = nullptr;
            func = nullptr; // no need to release
            if (ctx) {
                ctx->Release();
                ctx = nullptr;
            }
            built = false;
        }

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Script>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Script))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext &context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:
        Script():arguments(Array<Argument>(0)) {
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

        void setSourceCode(const char* source) {
            safeCopyStr(&this->source, source);
            built = false;
        }

        const char* getSourceCode() {
            return source;
        }

        __declspec(property(get = getSourceCode, put = setSourceCode)) const char* SourceCode;

        void setEntryPoint(const char* entryPoint) {
            safeCopyStr(&this->entryPoint, entryPoint);
            built = false;
        }

        const char* getEntryPoint()const {
            return entryPoint;
        }

        __declspec(property(get = getEntryPoint, put = setEntryPoint)) const char* EntryPoint;

        void setArguments(const Array<Argument>& arguments) {
            this->arguments = arguments;
        }

        __declspec(property(put = setArguments)) const Array<Argument>& Arguments;

        Status execute() {
            ctx->Prepare(func);
            for (size_t i = 0; i < arguments.Size; i++)
                arguments[i].set((asUINT)i, *ctx);
            int r = ctx->Execute();
            if (r != asEXECUTION_FINISHED) {
                if (r == asEXECUTION_EXCEPTION) {
                    Logger::log(LogType::ERR0R, _T("An exception '%hs' occurred. Please correct the code and try again.\n"), ctx->GetExceptionString());
                    return Status::SCRIPT_EXCEPTION;
                }
            }

            return Status::OK;
        }

        int getIntResult() {
            return ctx->GetReturnWord();
        }

        float getFloatResult() {
            return ctx->GetReturnFloat();
        }

        void *getObjectResult() {
            return ctx->GetReturnObject();
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::SCRIPT};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}