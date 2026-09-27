#include "ghedxpch.h"
#include "DxCubeMapLoader.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<IntrusivePointer<Image>> DxCubeMapLoader::loadSide(
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		WString side,
		uint32_t width,
		uint32_t height
	) {
		WString* imagePathAttribute = xml.findAttribute(side.Data);
		if (!imagePathAttribute) {
			auto message = std::format(_T("Required attribute '{}' on node 'CubeMap' is missing.\n"), side.Data);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		FilePath pathTop = FilePath(*imagePathAttribute);
		auto image = co_await resourceManager.load<Image>(pathTop, workingDir);
		if (width != 0 && height != 0) {
			if (image->Size.Width != width || image->Size.Height != height) {
				auto message = std::format(_T("Image '{}' doesn't match required size.\n"), side.Data);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
		}else{
			if (image->Size.Width != image->Size.Height) {
				auto message = std::format(_T("Image '{}' is not square.\n"), side.Data);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
		}

		co_return image;
	}

	CoroutineTask<void> DxCubeMapLoader::loadInternal(
		DxCubeMap& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"CubeMap");

		auto imageTop = co_await loadSide(xml, workingDir, L"top", 0, 0);
		auto imageBottom = co_await loadSide(xml, workingDir, L"bottom", imageTop->Size.Width, imageTop->Size.Height);
		auto imageLeft = co_await loadSide(xml, workingDir, L"left", imageTop->Size.Width, imageTop->Size.Height);
		auto imageRight = co_await loadSide(xml, workingDir, L"right", imageTop->Size.Width, imageTop->Size.Height);
		auto imageFront = co_await loadSide(xml, workingDir, L"front", imageTop->Size.Width, imageTop->Size.Height);
		auto imageBack = co_await loadSide(xml, workingDir, L"back", imageTop->Size.Width, imageTop->Size.Height);

		resource.init(imageTop.ref(), imageBottom.ref(), imageLeft.ref(), imageRight.ref(), imageFront.ref(), imageBack.ref(), memoryManager);
	}
}
