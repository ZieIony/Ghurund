#include "ghcpch.h"
#include "XMLReader.h"

#include <format>

namespace Ghurund::Core {
	void XMLReader::onInit() {
		HRESULT hr;
		if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&reader, nullptr))) {
			Logger::log(LogType::ERR0R, std::format(_T("Error creating xml reader, error is {}"), hr).c_str());
			throw CallFailedException();
		}
	}
}
