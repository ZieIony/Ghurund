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

    internal class IntPtrList : IList<IntPtr> {
        private readonly IntPtr ptr;

        public IntPtrList(IntPtr ptr) {
            this.ptr = ptr;
        }

        public IntPtr this[int index] { get => NativeLists.PointerList_get(ptr, index); set => NativeLists.PointerList_set(ptr, index, value); }

        public int Count => NativeLists.PointerList_Size(ptr);

        public bool IsReadOnly => false;

        public void Add(IntPtr item) {
            NativeLists.PointerList_add(ptr, item);
        }

        public void Clear() {
            NativeLists.PointerList_clear(ptr);
        }

        public bool Contains(IntPtr item) {
            return NativeLists.PointerList_contains(ptr, item);
        }

        public void CopyTo(IntPtr[] array, int arrayIndex) {
            throw new NotImplementedException();
        }

        public IEnumerator<IntPtr> GetEnumerator() {
            throw new NotImplementedException();
        }

        public int IndexOf(IntPtr item) {
            return NativeLists.PointerList_indexOf(ptr, item);
        }

        public void Insert(int index, IntPtr item) {
            NativeLists.PointerList_insert(ptr, index, item);
        }

        public bool Remove(IntPtr item) {
            return NativeLists.PointerList_remove(ptr, item);
        }

        public void RemoveAt(int index) {
            NativeLists.PointerList_removeAt(ptr, index);
        }

        IEnumerator IEnumerable.GetEnumerator() {
            throw new NotImplementedException();
        }
    }

    public class PointerListEnumerator<T> : IEnumerator<T> {
        private readonly IList<T> list;
        private int index = -1;

        public PointerListEnumerator(IList<T> list) {
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

    public abstract class PointerList<T> : IList<T> where T : NativeClass {
        IntPtrList pointers;

        public PointerList(IntPtr ptr) {
            pointers = new IntPtrList(ptr);
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
