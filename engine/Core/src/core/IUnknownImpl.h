#pragma once

#include <Unknwn.h>

namespace Ghurund::Core {
    template <typename InterfaceChain>
    class ComBase: public InterfaceChain {
    private:
        // No copy construction allowed.
        ComBase(const ComBase& b);
        ComBase& operator=(ComBase const&);

    protected:
        ULONG refValue;

    public:
        explicit ComBase() throw(): refValue(0) {}

        // IUnknown interface
        IFACEMETHOD(QueryInterface)(IID const& iid, OUT void** ppObject) {
            *ppObject = NULL;
            InterfaceChain::QueryInterfaceInternal(iid, ppObject);
            if (*ppObject == NULL)
                return E_NOINTERFACE;

            AddRef();
            return S_OK;
        }

        IFACEMETHOD_(ULONG, AddRef)() {
            return InterlockedIncrement(&refValue);
        }

        IFACEMETHOD_(ULONG, Release)() {
            ULONG newCount = InterlockedDecrement(&refValue);
            if (newCount == 0)
                delete this;

            return newCount;
        }

        virtual ~ComBase() {}
    };


    struct QiListEmpty {};

    template <typename InterfaceName, typename InterfaceChain>
    class QiListSelf: public InterfaceChain {
    public:
        inline void QueryInterfaceInternal(IID const& iid, OUT void** ppObject) throw() {
            if (iid != __uuidof(InterfaceName))
                return InterfaceChain::QueryInterfaceInternal(iid, ppObject);

            *ppObject = (InterfaceName*)this;
        }
    };

    template <typename InterfaceName, typename InterfaceChain = QiListEmpty>
    class QiList: public InterfaceName, public InterfaceChain {
    public:
        inline void QueryInterfaceInternal(IID const& iid, OUT void** ppObject) throw() {
            if (iid != __uuidof(InterfaceName))
                return InterfaceChain::QueryInterfaceInternal(iid, ppObject);

            *ppObject = (InterfaceName*)this;
        }
    };


    template <typename InterfaceName>
    class QiList<InterfaceName, QiListEmpty>: public InterfaceName {
    public:
        inline void QueryInterfaceInternal(IID const& iid, OUT void** ppObject) throw() {
            if (iid != __uuidof(InterfaceName))
                return;

            *ppObject = (InterfaceName*)this;
        }
    };
}