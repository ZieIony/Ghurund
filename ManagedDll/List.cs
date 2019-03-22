using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    internal static class NativeLists {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int List_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void List_add(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void List_insert(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool List_remove(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool List_removeAt(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr List_get(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void List_set(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void List_clear(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool List_contains(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int List_indexOf(IntPtr _this, IntPtr item);
    }

    public class ListEnumerator<T> : IEnumerator<T> {
        private readonly IList<T> list;
        private int index = -1;

        public ListEnumerator(IList<T> list) {
            this.list = list;
        }

        public T Current => list[index];

        object IEnumerator.Current => list[index];

        public void Dispose() {
        }

        public bool MoveNext() {
            index++;
            return index < list.Count;
        }

        public void Reset() {
            index = -1;
        }
    }

    public class List<T> : NativeClass, IList<T> where T : NativeClass {

        private readonly MakeNativeObjectDelegate<T> makeNativeObjectDelegate;

        public List() {
        }

        public List(IntPtr ptr, MakeNativeObjectDelegate<T> makeNativeObjectDelegate) : base(ptr) {
            this.makeNativeObjectDelegate = makeNativeObjectDelegate;
        }

        public T this[int index] {
            get {
                var itemPtr = NativeLists.List_get(NativePtr, index);
                return itemPtr == IntPtr.Zero ? null : makeNativeObjectDelegate.Invoke(itemPtr);
            }

            set => NativeLists.List_set(NativePtr, index, value.NativePtr);
        }

        public int Count => NativeLists.List_Size(NativePtr);

        public bool IsReadOnly => false;

        public void Add(T item) => NativeLists.List_add(NativePtr, item.NativePtr);

        public void Clear() => NativeLists.List_clear(NativePtr);

        public bool Contains(T item) => NativeLists.List_contains(NativePtr, item.NativePtr);

        public void CopyTo(T[] array, int arrayIndex) => throw new NotImplementedException();

        public IEnumerator<T> GetEnumerator() => new ListEnumerator<T>(this);

        public int IndexOf(T item) => NativeLists.List_indexOf(NativePtr, item.NativePtr);

        public void Insert(int index, T item) => NativeLists.List_insert(NativePtr, index, item.NativePtr);

        public bool Remove(T item) => NativeLists.List_remove(NativePtr, item.NativePtr);

        public void RemoveAt(int index) => NativeLists.List_removeAt(NativePtr, index);

        IEnumerator IEnumerable.GetEnumerator() => new ListEnumerator<T>(this);
    }
}
