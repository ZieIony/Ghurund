#pragma once

#include "core/string/String.h"
#include "core/EnumOperators.h"

namespace Ghurund::Core {
	enum class ResourceFormatOptions {
        CAN_SAVE = 1, CAN_LOAD = 2
    };

    class ResourceFormat {
    public:
        static const ResourceFormat AUTO;

        const WString extension;
        const bool canSave, canLoad;

		ResourceFormat(const WString& extension, ResourceFormatOptions options = (ResourceFormatOptions)0):
			extension(extension),
            canSave((options& ResourceFormatOptions::CAN_SAVE) == ResourceFormatOptions::CAN_SAVE),
            canLoad((options& ResourceFormatOptions::CAN_LOAD) == ResourceFormatOptions::CAN_LOAD) {
		}

        ResourceFormat(const ResourceFormat& format): extension(format.extension), canSave(format.canSave), canLoad(format.canLoad) {}

        inline bool operator==(const ResourceFormat& format) const {
            return extension == format.extension && canSave == format.canSave && canLoad == format.canLoad;
        }
    };
}
