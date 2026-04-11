#pragma once

#include "Object.h"

#ifdef _DEBUG
#include "core/StackTrace.h"
#include "core/collection/List.h"
#include "core/threading/CriticalSection.h"
#endif

namespace Ghurund::Core {

	class RefCountedObject: public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = RefCountedObject::GET_TYPE();
#pragma endregion

    private:
        mutable uint32_t referenceCount = 1;

#ifdef _DEBUG
        static List<RefCountedObject*> pointers;
        static CriticalSection criticalSection;
        static bool pointersListResizeLocked;

        List<StackTraceEntry> stacktrace;

        void checkReferenceCount() const;
#endif

    private:
        RefCountedObject& operator=(const RefCountedObject& other) = delete;

    protected:
        RefCountedObject(const RefCountedObject& pointer) = delete;

        virtual ~RefCountedObject()
        //    = 0  // TODO: a destructor cannot be abstract
        ;

    public:
        RefCountedObject();

        /**
         * @brief Increases reference count by 1.
        */
        inline void addReference() const {
            referenceCount++;
        }

        /**
         * @brief Decreases reference count of this object by one. If the reference count reaches 0, the object is deleted.
        */
        inline void release() const {
#ifdef _DEBUG
            checkReferenceCount();
#endif
            referenceCount--;
            if (!referenceCount)
                delete this;
        }

        uint32_t getReferenceCount() const {
            return referenceCount;
        }

        __declspec(property(get = getReferenceCount)) uint32_t ReferenceCount;

        virtual String toString() const override;

#ifdef _DEBUG
        static void setPointersListResizeLocked(bool locked) {
            SectionLock lock(criticalSection);
            pointersListResizeLocked = locked;
        }

        static size_t numberOfAllocatedPointers() {
            SectionLock lock(criticalSection);
            return pointers.Size;
        }

        static void dumpPointers();

        static void reservePointers(size_t size) {
            SectionLock lock(criticalSection);
            pointers.resize(size);
        }

        static void clearPointers() {
            SectionLock lock(criticalSection);
            for (RefCountedObject* p : pointers)
                delete p;
            pointers.clear();
        }
#endif
    };

    /**
     * @brief Safely sets a RefCountedObject object to a new value. The previous RefCountedObject has its reference counter decreased by one,
     * and the new RefCountedObject has its reference counter increased by one.
     * @tparam Type
     * @param pointer A reference to a RefCountedObject address to assign another RefCountedObject to. The address can be null.
     * @param pointer2 A RefCountedObject address to assign to 'pointer'. Can be null.
    */
    template<class Type>
    void setPointer(Type*& pointer, Type* pointer2) {
        if (pointer2 != nullptr)
            pointer2->addReference();
        if (pointer != nullptr)
            pointer->release();
        pointer = pointer2;
    }

    /**
     * @brief Safely releases and clears a RefCountedObject object.
     * @tparam Type
     * @param pointer
    */
    template<class Type>
    void safeRelease(Type*& pointer) {
        if (pointer != nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }

    class RefCountedObjectDeleter {
    public:
        inline void operator()(RefCountedObject* obj) {
            if(obj)
                obj->release();
        }
    };
}
