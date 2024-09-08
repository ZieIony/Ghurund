#pragma once

#include "DisplayMode.h"
#include "core/SharedPointer.h"
#include "core/collection/List.h"
#include "core/string/String.h"

#include <wrl.h>

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class AdapterOutput{
    private:
        DXGI_OUTPUT_DESC desc;
        WString name;
        ComPtr<IDXGIOutput> output;
        List<SharedPointer<DisplayMode>> displayModes;

        void initModes();

    public:
        AdapterOutput(ComPtr<IDXGIOutput> output);

        AdapterOutput(const AdapterOutput& other):
            desc(other.desc), name(other.name), output(other.output), displayModes(other.displayModes) {}

        AdapterOutput(AdapterOutput&& other) noexcept:
            desc(std::move(other.desc)), name(std::move(other.name)), output(std::move(other.output)), displayModes(std::move(other.displayModes)) {
            other.desc = {};
            other.name = {};
            other.output = nullptr;
            other.displayModes.clear();
        }

        const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const WString& Name;

        const List<SharedPointer<DisplayMode>>& getDisplayModes() const {
            return displayModes;
        }

        __declspec(property(get = getDisplayModes)) const List<SharedPointer<DisplayMode>>& DisplayModes;
    };
}