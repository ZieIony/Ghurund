#include "ghepch.h"
#include "ScriptLoader.h"

namespace Ghurund::Engine {
    Resource* ScriptLoader::loadInternal(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        Script* script = makeResource<Script>();
        script->EntryPoint = stream.readASCII();
        script->SourceCode = stream.readASCII();
        script->build(engine);
        return script;
    }

    void ScriptLoader::saveInternal(
        MemoryOutputStream& stream,
        const DirectoryPath& workingDir,
        Resource& resource,
        const ResourceFormat& format,
        SaveOption options
    ) const {
        Script& script = (Script&)resource;
        if (script.EntryPoint.Length == 0 || script.SourceCode.Length == 0)
            throw InvalidDataException("the script is empty");
        stream.writeASCII(script.EntryPoint.Data);
        stream.writeASCII(script.SourceCode.Data);
    }
}