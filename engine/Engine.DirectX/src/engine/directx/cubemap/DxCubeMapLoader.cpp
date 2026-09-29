#include "ghedxpch.h"
#include "DxCubeMapLoader.h"

#include "engine/directx/texture/DxTextureLoader.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<List<IntrusivePointer<Image>>> DxCubeMapLoader::loadFace(
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		WString side,
		IntSize size,
		const ResourceFormat& format,
		LoadOptions options
	) {
		auto imageElement = xml.findElement(side.Data);
		if (!imageElement) {
			auto message = std::format(_T("Required node '{}' on node 'CubeMap' is missing.\n"), side.Data);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		auto images = co_await DxTextureLoader::loadMipImages(resourceManager, *imageElement, workingDir, format, options);
		co_return images;
	}

	CoroutineTask<void> DxCubeMapLoader::loadInternal(
		DxCubeMap& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"CubeMap");

		auto imagesTop = co_await loadFace(xml, workingDir, L"FaceTop", { 0, 0 }, format, options);
		auto size = imagesTop[0]->Size;

		auto imagesBottom = co_await loadFace(xml, workingDir, L"FaceBottom", size, format, options);
		if (imagesBottom.Size != imagesTop.Size) {
			auto message = std::format(_T("Number of bottom mip images ({}) differs from number of top mip images ({}).\n"), imagesBottom.Size, imagesTop.Size);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		if (imagesBottom[0]->Format != imagesTop[0]->Format) {
			auto message = std::format(_T("Format of bottom mip images ({}) differs from format of top mip images ({}).\n"), (uint32_t)imagesBottom[0]->Format, (uint32_t)imagesTop[0]->Format);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		auto imagesLeft = co_await loadFace(xml, workingDir, L"FaceLeft", size, format, options);
		if (imagesLeft.Size != imagesTop.Size) {
			auto message = std::format(_T("Number of left mip images ({}) differs from number of top mip images ({}).\n"), imagesLeft.Size, imagesTop.Size);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		if (imagesLeft[0]->Format != imagesTop[0]->Format) {
			auto message = std::format(_T("Format of left mip images ({}) differs from format of top mip images ({}).\n"), (uint32_t)imagesLeft[0]->Format, (uint32_t)imagesTop[0]->Format);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		auto imagesRight = co_await loadFace(xml, workingDir, L"FaceRight", size, format, options);
		if (imagesRight.Size != imagesTop.Size) {
			auto message = std::format(_T("Number of right mip images ({}) differs from number of top mip images ({}).\n"), imagesRight.Size, imagesTop.Size);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		if (imagesRight[0]->Format != imagesTop[0]->Format) {
			auto message = std::format(_T("Format of right mip images ({}) differs from format of top mip images ({}).\n"), (uint32_t)imagesRight[0]->Format, (uint32_t)imagesTop[0]->Format);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		auto imagesFront = co_await loadFace(xml, workingDir, L"FaceFront", size, format, options);
		if (imagesFront.Size != imagesTop.Size) {
			auto message = std::format(_T("Number of front mip images ({}) differs from number of top mip images ({}).\n"), imagesFront.Size, imagesTop.Size);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		if (imagesFront[0]->Format != imagesTop[0]->Format) {
			auto message = std::format(_T("Format of front mip images ({}) differs from format of top mip images ({}).\n"), (uint32_t)imagesFront[0]->Format, (uint32_t)imagesTop[0]->Format);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		auto imagesBack = co_await loadFace(xml, workingDir, L"FaceBack", size, format, options);
		if (imagesBack.Size != imagesTop.Size) {
			auto message = std::format(_T("Number of back mip images ({}) differs from number of top mip images ({}).\n"), imagesBack.Size, imagesTop.Size);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}
		if (imagesBack[0]->Format != imagesTop[0]->Format) {
			auto message = std::format(_T("Format of back mip images ({}) differs from format of top mip images ({}).\n"), (uint32_t)imagesBack[0]->Format, (uint32_t)imagesTop[0]->Format);
			Logger::logAndThrow<InvalidDataException>(message.c_str());
		}

		resource.init(imagesTop, imagesBottom, imagesLeft, imagesRight, imagesFront, imagesBack, memoryManager);
	}
}
