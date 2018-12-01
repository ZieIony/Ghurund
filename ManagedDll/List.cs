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

    public class PointerList : IList<IntPtr> {
        private readonly IntPtr ptr;

        public PointerList(IntPtr ptr) {
            this.ptr = ptr;
        }

        public IntPtr this[int index] { get => NativeLists.List_get(ptr, index); set => NativeLists.List_set(ptr, index, value); }

        public int Count => NativeLists.List_Size(ptr);

        public bool IsReadOnly => false;

        public void Add(IntPtr item) {
            NativeLists.List_add(ptr, item);
        }

        public void Clear() {
            NativeLists.List_clear(ptr);
        }

        public bool Contains(IntPtr item) {
            return NativeLists.List_contains(ptr, item);
        }

        public void CopyTo(IntPtr[] array, int arrayIndex) {
            throw new NotImplementedException();
        }

        public IEnumerator<IntPtr> GetEnumerator() {
            throw new NotImplementedException();
        }

        public int IndexOf(IntPtr item) {
            return NativeLists.List_indexOf(ptr, item);
        }

        public void Insert(int index, IntPtr item) {
            NativeLists.List_insert(ptr, index, item);
        }

        public bool Remove(IntPtr item) {
            return NativeLists.List_remove(ptr, item);
        }

        public void RemoveAt(int index) {
            NativeLists.List_removeAt(ptr, index);
        }

        IEnumerator IEnumerable.GetEnumerator() {
            throw new NotImplementedException();
        }
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

    public abstract class List<T> : IList<T> where T : NativeClass {
        PointerList pointers;

        public List(IntPtr ptr) {
            pointers = new PointerList(ptr);
        }

        protected abstract T MakeItem(IntPtr p);

        public T this[int index] {
            get => MakeItem(pointers[index]);
            set {
                pointers[index] = value.NativePtr;
            }
        }

        public int Count => pointers.Count;

        public bool IsReadOnly => pointers.IsReadOnly;

        public void Add(T item) {
            pointers.Add(item.NativePtr);
        }

        public void Clear() {
            pointers.Clear();
        }

        public bool Contains(T item) {
            return pointers.Contains(item.NativePtr);
        }

        public void CopyTo(T[] array, int arrayIndex) {
            throw new NotImplementedException();
        }

        public IEnumerator<T> GetEnumerator() {
            return new ListEnumerator<T>(this);
        }

        public int IndexOf(T item) {
            return pointers.IndexOf(item.NativePtr);
        }

        public void Insert(int index, T item) {
            pointers.Insert(index, item.NativePtr);
        }

        public bool Remove(T item) {
            return pointers.Remove(item.NativePtr);
        }

        public void RemoveAt(int index) {
            pointers.RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return new ListEnumerator<T>(this);
        }
    }
}
