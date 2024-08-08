#include "ghpch.h"
#include "Script.h"

#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/TypeBuilder.h"
#include "core/logging/Logger.h"
#include "ScriptExecutionException.h"

#include <angelscript.h>

#include "ScriptEngine.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& Script::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Script>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Script>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Script))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Script::build(ScriptEngine& engine) {
        mod = engine.makeModule();

        auto r = mod->AddScriptSection("main", source.Data, source.Length);
        assert(r >= 0);

        if (mod->Build() < 0) {
            Logger::log(LogType::ERR0R, _T("Compilation failed.\n"));
            throw InvalidDataException();
        }

        func = mod->GetFunctionByDecl(entryPoint.Data);
        if (func == 0) {
            // The function couldn't be found. Instruct the script writer
            // to include the expected function in the script.
            auto text = std::format(_T("The script must have the function '%hs'. Please add it and try again.\n"), entryPoint);
            Logger::log(LogType::ERR0R, text.c_str());
            throw InvalidDataException();
        }

        // Create our context, prepare it, and then execute
        ctx = engine.createContext();

        built = true;
    }

    void Script::execute() {
        ctx->Prepare(func);
        for (size_t i = 0; i < arguments.Size; i++)
            ctx->SetArgAddress((asUINT)i, arguments[i]);
        int r = ctx->Execute();
        if (r != asEXECUTION_FINISHED) {
            if (r == asEXECUTION_EXCEPTION) {
                auto text = std::format(_T("An exception '%s' occurred. Please correct the code and try again.\n"), AString(ctx->GetExceptionString()));
                Logger::log(LogType::ERR0R, text.c_str());
                throw ScriptExecutionException();
            }
        }
    }
}