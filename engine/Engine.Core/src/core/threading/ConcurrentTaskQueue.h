#pragma once

#include "Waitable.h"
#include "core/collection/Queue.h"
#include "core/threading/CriticalSection.h"
#include "core/threading/Task.h"

namespace Ghurund::Core {
    class ConcurrentTaskQueue {
    private:
        Queue<SharedPointer2<Task>> queue;
        CriticalSection criticalSection;

    public:
        inline void add(SharedPointer2<Task> task) {
            criticalSection.enter();
            queue.add(task);
            criticalSection.leave();
        }

        inline SharedPointer2<Task> remove() {
            criticalSection.enter();
            SharedPointer2<Task> task;
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