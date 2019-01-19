using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Collection {
    internal static class NativeLists {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int PointerList_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PointerList_add(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PointerList_insert(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool PointerList_remove(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool PointerList_removeAt(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PointerList_get(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PointerList_set(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PointerList_clear(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool PointerList_contains(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int PointerList_indexOf(IntPtr _this, IntPtr item);
    }

    public class PointerList<T> : NativeClass, IList<T> where T : NativeClass {

        private MakeNativeObjectDelegate<T> makeNativeObjectDelegate;

        public PointerList(IntPtr ptr, MakeNativeObjectDelegate<T> makeNativeObjectDelegate) : base(ptr) {
            this.makeNativeObjectDelegate = makeNativeObjectDelegate;
        }

        public T this[int index] {
            get => makeNativeObjectDelegate.Invoke(NativeLists.PointerList_get(NativePtr, index));
            set => NativeLists.PointerList_set(NativePtr, index, value.NativePtr);
        }

        public int Count => NativeLists.PointerList_Size(NativePtr);

        public bool IsReadOnly => false;

        public void Add(T item) => NativeLists.PointerList_add(NativePtr, item.NativePtr);

        public void Clear() => NativeLists.PointerList_clear(NativePtr);

        public bool Contains(T item) => NativeLists.PointerList_contains(NativePtr, item.NativePtr);

        public void CopyTo(T[] array, int arrayIndex) => throw new NotImplementedException();

        public IEnumerator<T> GetEnumerator() => new ListEnumerator<T>(this);

        public int IndexOf(T item) => NativeLists.PointerList_indexOf(NativePtr, item.NativePtr);

        public void Insert(int index, T item) => NativeLists.PointerList_insert(NativePtr, index, item.NativePtr);

        public bool Remove(T item) => NativeLists.PointerList_remove(NativePtr, item.NativePtr);

        public void RemoveAt(int index) => NativeLists.PointerList_removeAt(NativePtr, index);

        IEnumerator IEnumerable.GetEnumerator() => new ListEnumerator<T>(this);
    }
}
