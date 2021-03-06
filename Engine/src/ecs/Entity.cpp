#include "ghpch.h"
#include "Entity.h"

#include "core/io/File.h"
#include "core/io/MemoryStream.h"
#include "resource/ResourceContext.h"

namespace Ghurund {

    Status Entity::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        Name = stream.readUnicode();
        uint32_t componentCount = stream.readUInt();
        for (uint32_t i = 0; i < componentCount; i++) {
            const char* typeNamespace = stream.readASCII();
            const char* typeName = stream.readASCII();
            Ghurund::Type* type = Type::fromName(typeNamespace, typeName);
            if (!type)
                return Logger::log(LogType::ERR0R, Status::UNKNOWN_TYPE, _T("Attempted to load an unknown type.\n"));
            Allocator* allocator = context.Allocators.get(*type);
            if (!allocator)
                return Logger::log(LogType::ERR0R, Status::MISSING_ALLOCATOR, _T("Allocator is missing for components of type {}::{}\n"), typeNamespace, typeName);
            if (!type->Constructor)
                return Logger::log(LogType::ERR0R, Status::MISSING_CONSTRUCTOR, _T("Type {}::{} is missing a constructor.\n"), typeNamespace, typeName);
            Component* obj = (Component*)type->Constructor->newInstance(*allocator);
        }
        return Status::OK;
    }

    Status Entity::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        stream.writeUnicode(Name.Data);
        stream.writeUInt((uint32_t)components.Size);
        for (Component* c : components) {
            stream.writeASCII(c->Type.Namespace);
            stream.writeASCII(c->Type.Name);
            c->save(context, workingDir, stream, options);
        }
        return Status::OK;
    }

    const Ghurund::Type& Entity::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Entity>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Entity))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}