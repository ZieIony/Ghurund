#pragma once

#include "resource/Resource.h"
#include "core/string/AString.h"

#include "angelscript.h"

namespace Ghurund {
    class ScriptEngine;
    class ResourceManager;
    class ResourceContext;

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

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Script>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Script))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext &context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

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