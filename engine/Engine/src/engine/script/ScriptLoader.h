#pragma once

#include "Script.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ScriptLoader:public Loader {
	private:
		ScriptEngine& engine;

	protected:
		virtual Resource* loadInternal(
			NotNull<MemoryInputStream> stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

		virtual void saveInternal(
			NotNull<MemoryOutputStream> stream,
			const DirectoryPath& workingDir,
			Resource& resource,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		ScriptLoader(ScriptEngine& engine):engine(engine) {}
	};
}