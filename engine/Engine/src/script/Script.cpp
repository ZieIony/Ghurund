#include "ghpch.h"
#include "Script.h"

#include "ScriptEngine.h"
#include "core/io/File.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
    Status Script::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        /*EntryPoint = stream.readASCII();
        SourceCode = stream.readASCII();
        return build(context.ScriptEngine);*/
        return Status::NOT_IMPLEMENTED;
    }

    Status Script::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        if (entryPoint.Length == 0 || source.Length == 0)
            return Status::INV_STATE;
        stream.writeASCII(entryPoint.Data);
        stream.writeASCII(source.Data);
        return Status::OK;
    }

    const Ghurund::Core::Type& Script::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Script>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Script>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Script))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status Script::build(ScriptEngine& engine) {
        mod = engine.makeModule();

        auto r = mod->AddScriptSection("main", source.Data, source.Length);
        assert(r >= 0);

        if (mod->Build() < 0)
            return Logger::log(LogType::ERR0R, Status::COMPILATION_ERROR, _T("Compilation failed.\n"));

        func = mod->GetFunctionByDecl(entryPoint.Data);
        if (func == 0)
            // The function couldn't be found. Instruct the script writer
            // to include the expected function in the script.
            return Logger::log(LogType::ERR0R, Status::ENTRY_POINT_NOT_FOUND, _T("The script must have the function '%hs'. Please add it and try again.\n"), entryPoint);

        // Create our context, prepare it, and then execute
        ctx = engine.createContext();

        built = true;

        return Status::OK;
    }

    Status Script::execute() {
        ctx->Prepare(func);
        for (size_t i = 0; i < arguments.Size; i++)
            ctx->SetArgAddress((asUINT)i, arguments[i]);
        int r = ctx->Execute();
        if (r != asEXECUTION_FINISHED) {
            if (r == asEXECUTION_EXCEPTION) {
                Logger::log(LogType::ERR0R, _T("An exception '%hs' occurred. Please correct the code and try again.\n"), convertText<char, tchar>(AString(ctx->GetExceptionString())));
                return Status::SCRIPT_EXCEPTION;
            }
        }

        return Status::OK;
    }
}