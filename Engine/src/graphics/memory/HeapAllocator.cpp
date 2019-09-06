#include "HeapAllocator.h"
#include "MathUtils.h"
#include "graphics/Graphics.h"
#include "core/allocation/CircularBufferStrategy.h"

namespace Ghurund {
    HeapAllocator::HeapAllocator(Graphics& graphics, memory_t size, AllocationStrategy* strategy, D3D12_HEAP_TYPE type, D3D12_HEAP_FLAGS flags) {
        this->strategy = strategy == nullptr ? ghnew CircularBufferStrategy() : strategy;
        this->strategy->init(size, 64_KB, 64_KB);
        CD3DX12_HEAP_DESC desc(this->strategy->Size, type, 0, flags);
        if (FAILED(graphics.Device->CreateHeap(&desc, IID_PPV_ARGS(&heap))))
            Logger::log(LogType::ERR0R, _T("failed to create heap\n"));
    }
}