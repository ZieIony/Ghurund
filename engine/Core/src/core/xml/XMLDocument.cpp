#include "ghcpch.h"
#include "XMLDocument.h"

#include <Shlwapi.h>

#pragma comment(lib, "xmllite.lib")

namespace Ghurund::Core {
	void XMLDocument::parse(const void* data, uint32_t size) {
		root.set(nullptr);
		CreateXmlReader(__uuidof(IXmlReader), (void**)&reader, nullptr);
		Microsoft::WRL::ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)data, (UINT)size);
		reader->SetInput(memStream.Get());
		XmlNodeType nodeType;
		List<SharedPointer<XMLElement>> elementStack;
		while (SUCCEEDED(reader->Read(&nodeType))) {
			switch (nodeType) {
			case XmlNodeType_Element:
			{
				auto element = makeShared<XMLElement>();
				element->name = readName();
				bool empty = reader->IsEmptyElement();

				if (reader->MoveToFirstAttribute() == S_OK) {
					element->attributes.put(readName(), readValue());
					while (reader->MoveToNextAttribute() == S_OK)
						element->attributes.put(readName(), readValue());
				}

				if (!elementStack.Empty)
					elementStack[elementStack.Size - 1]->children.add(element);
				if (!empty)
					elementStack.add(element);
			}
			break;
			case XmlNodeType_EndElement:
				if (elementStack.Size == 1)
					root = elementStack[0];
				elementStack.removeAt(elementStack.Size - 1);
				break;
			case XmlNodeType_Text:
				elementStack[elementStack.Size - 1]->value = readValue();
				break;
			}
		}
		if (root == nullptr)
			throw InvalidDataException();
	}
}
