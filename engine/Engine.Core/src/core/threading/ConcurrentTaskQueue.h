#pragma once

#include "Waitable.h"
#include "core/collection/Queue.h"
#include "core/threading/CriticalSection.h"
#include "core/threading/Task.h"

namespace Ghurund {
    class ConcurrentTaskQueue {
    private:
        Queue<SharedPointer<Task>> queue;
        CriticalSection criticalSection;

    public:
        inline void add(SharedPointer<Task> task) {
            criticalSection.enter();
            queue.add(task);
            criticalSection.leave();
        }

        inline SharedPointer<Task> remove() {
            criticalSection.enter();
            SharedPointer<Task> task = nullptr;
            if (!queue.Empty) {
                task = queue.front();
                queue.remove();
            }
            criticalSection.leave();
            return task;
        }

        inline size_t getSize() {
            criticalSection.enter();
            size_t size = queue.Size;
            criticalSection.leave();
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void clear() {
            criticalSection.enter();
            queue.clear();
            criticalSection.leave();
        }
    };
}