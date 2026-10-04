#include "ghedxpch.h"
#include "DxTextureLoader.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<void> DxTextureLoader::loadInternal(
		DxTexture& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"Texture", DxTexture::FORMAT_XML);
		auto images = co_await loadMipImages(resourceManager, xml, workingDir, format, options);
		resource.init(images, memoryManager);
	}

	CoroutineTask<List<IntrusivePointer<Image>>> DxTextureLoader::loadMipImages(
		ResourceManager& resourceManager,
		const XMLElement & xml,
		const DirectoryPath & workingDir,
		const ResourceFormat & format,
		LoadOptions options
	) {
		struct ImageInfo {
			uint32_t level;
			FilePath path;
		};

		bool generateMipMaps = xml.getAttributeValue<bool>(L"generateMipMaps", false);
		List<ImageInfo> imageInfos;
		for (auto& child : xml.children) {
			if (child->name == L"Image") {
				auto level = child->getAttributeValue<uint32_t>(L"mipLevel", 0);
				auto path = child->requireAttribute(L"path");
				imageInfos.add(ImageInfo(level, FilePath(path)));
			}
		}
		if (imageInfos.IsEmpty)
			Logger::logAndThrow<InvalidDataException>(_T("Missing required at least one 'Image' node.\n"));

		if (imageInfos.Size > 1 && generateMipMaps)
			Logger::logAndThrow<InvalidDataException>(_T("Combination of 'generateMipMaps' attribute == true and more than one 'Image' node is invalid.\n"));

		List<IntrusivePointer<Image>> images;
		DXGI_FORMAT imageFormat = DXGI_FORMAT_UNKNOWN;
		for (size_t i = 0; i < imageInfos.Size;i++) {
			auto index = imageInfos.find([&](const ImageInfo& info) {return info.level == i; });
			if (index == imageInfos.Size) {
				auto message = std::format(_T("Image for mipLevel {} is missing.\n"), i);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
			auto imageInfo = imageInfos[i];
			auto image = co_await resourceManager.load<Image>(imageInfo.path, workingDir);
			if (imageFormat != DXGI_FORMAT_UNKNOWN && imageFormat != image->Format) {
				auto message = std::format(
					_T("Image format {} of image '{}' differs from the first loaded format ({}).\n"),
					(uint32_t)image->Format, imageInfo.path.toString(), (uint32_t)imageFormat
				);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
			imageFormat = image->Format;
			images.add(image);
		}
		if (imageInfos.IsEmpty && generateMipMaps) {
			throw NotImplementedException();
		}

		co_return images;
	}
}
