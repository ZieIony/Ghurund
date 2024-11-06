#include "ghcpch.h"

namespace Ghurund::Core {
	TypeName TypeName::parse(const AString& typeidName) {
		size_t templateParamsIndex = typeidName.find("<");
		size_t space = typeidName.find("class ");	// built-in basic types don't start with 'class'
		AString nameWithNamespace = space < typeidName.Length ? typeidName.substring(space + strlen("class ")).trim() : typeidName;
		size_t nameSeparatorIndex = nameWithNamespace.findLast("::", templateParamsIndex);
		AString name, _namespace;
		if (nameSeparatorIndex != nameWithNamespace.Length) {
			name = nameWithNamespace.substring(nameSeparatorIndex + 2).trim();
			_namespace = nameWithNamespace.substring(0, nameSeparatorIndex).trim();
		} else {
			name = nameWithNamespace;
		}
		List<AString> templateParams;
#ifdef _DEBUG
		if (templateParamsIndex != typeidName.Length) {
			size_t currentTemplateParamIndex = templateParamsIndex + 1;
			int braceStack = 0;
			for (size_t i = currentTemplateParamIndex; i < typeidName.Length; i++) {
				if (typeidName[i] == '<') {
					braceStack++;
				} else if (typeidName[i] == '>') {
					braceStack--;
					if (braceStack <= 0) {
						templateParams.add(typeidName.substring(currentTemplateParamIndex, i).trim());
						i = typeidName.find(",", i);
						currentTemplateParamIndex = i + 1;
					}
				} else if (braceStack == 0 && (typeidName[i] == ',' || i == typeidName.Length - 1)) {
					templateParams.add(typeidName.substring(currentTemplateParamIndex, i).trim());
					i = typeidName.find(",", i);
					currentTemplateParamIndex = i + 1;
				}
			}
		}
#endif
		return { _namespace, name, templateParams };
	}
}
