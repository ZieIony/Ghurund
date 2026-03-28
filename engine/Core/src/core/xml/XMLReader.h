#pragma once

#include "core/object/Initializable.h"

#include <xmllite.h>

namespace Ghurund::Core {
	class XMLReader:public Initializable {
	private:
		IXmlReader* reader;

	protected:
		virtual void onInit() override;

	public:
		void parse(const void* data, size_t size) {
			Microsoft::WRL::ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)data, (UINT)size);
			reader->SetInput(memStream.Get());
			XmlNodeType nodeType;
			reader->Read(&nodeType);
		}
	};
}
