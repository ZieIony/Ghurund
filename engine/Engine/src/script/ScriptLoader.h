#pragma once

#include "Script.h"
#include "core/resource/Loader.h"

namespace Ghurund {
	using namespace Ghurund::Core;

	class ScriptLoader:public Loader {
	private:
		ScriptEngine& engine;

	public:
		ScriptLoader(ScriptEngine& engine):engine(engine) {}

		virtual Script* load(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) override;

		virtual void save(
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			Resource& resource,
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const override;
	};
}