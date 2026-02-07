#pragma once

#include "Common.h"

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	class CommandLine {
	private:
		List<AString> arguments;
		Map<AString, AString> parameters;

	public:
		CommandLine(const AString& commandLine = GetCommandLineA()) {
			Array<AString> items = commandLine.split(" ");
			for (size_t i = 0; i < items.Size; i++) {
				Array<AString> keyVal = items[i].split("=");
				if (keyVal.Size != 2) {
					arguments.add(items[i]);
				} else {
					parameters.put(keyVal[0], keyVal[1]);
				}
			}
		}

		inline const List<AString>& getArguments() const {
			return arguments;
		}

		__declspec(property(get = getArguments)) const List<AString>& Arguments;

		inline const Map<AString, AString>& getParameters() const {
			return parameters;
		}

		__declspec(property(get = getParameters)) const Map<AString, AString>& Parameters;
	};
}