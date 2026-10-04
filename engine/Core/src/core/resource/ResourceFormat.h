#pragma once

#include "core/string/String.h"
#include "core/EnumOperators.h"

namespace Ghurund::Core {
	enum class ResourceFormatOptions {
		CAN_SAVE = 1, CAN_LOAD = 2
	};

	class ResourceFormat {
	private:
		WString extension;
		bool canSave, canLoad;
		uint32_t version = 0;

	public:
		static const ResourceFormat AUTO;

		ResourceFormat(
			const WString& fileExtension,
			ResourceFormatOptions options = (ResourceFormatOptions)0,
			uint32_t version = 0
		):
			extension(fileExtension),
			canSave((options& ResourceFormatOptions::CAN_SAVE) == ResourceFormatOptions::CAN_SAVE),
			canLoad((options& ResourceFormatOptions::CAN_LOAD) == ResourceFormatOptions::CAN_LOAD),
			version(version) {
		}

		ResourceFormat(
			const ResourceFormat& other
		): extension(other.extension), canSave(other.canSave), canLoad(other.canLoad), version(other.version) {}

		ResourceFormat(
			ResourceFormat&& other
		) noexcept: extension(other.extension), canSave(other.canSave), canLoad(other.canLoad), version(other.version) {}

		inline const WString& getFileExtension() const {
			return extension;
		}

		__declspec(property(get = getFileExtension)) const WString& FileExtension;

		inline bool getCanSave() const {
			return canSave;
		}

		__declspec(property(get = getCanSave)) bool CanSave;

		inline bool getCanLoad() const {
			return canLoad;
		}

		__declspec(property(get = getCanLoad)) bool CanLoad;

		inline uint32_t getVersion() const {
			return version;
		}

		__declspec(property(get = getVersion)) uint32_t Version;

		inline ResourceFormat operator=(const ResourceFormat& other) {
			extension = other.extension;
			canSave = other.canSave;
			canLoad = other.canLoad;
			version = other.version;
			return *this;
		}

		inline ResourceFormat operator=(ResourceFormat&& other) noexcept {
			extension = other.extension;
			canSave = other.canSave;
			canLoad = other.canLoad;
			version = other.version;
			return *this;
		}

		inline bool operator==(const ResourceFormat& other) const {
			return extension == other.extension && canSave == other.canSave && canLoad == other.canLoad && version == other.version;
		}
	};
}
