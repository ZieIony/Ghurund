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

    public abstract class NativeList<T> : IList<T> where T : NativeClass {
        List<T> managedItems = new List<T>();
        PointerList pointers;

        public NativeList(IntPtr ptr) {
            pointers = new PointerList(ptr);
            SyncList();
        }

        public void SyncList() {
            managedItems.Clear();
            for (int i = 0; i < pointers.Count; i++)
                managedItems.Add(MakeItem(pointers[i]));
        }

        protected abstract T MakeItem(IntPtr p);

        public T this[int index] {
            get => managedItems[index];
            set {
                managedItems[index] = value;
                pointers[index] = value.NativePtr;
            }
        }

        public int Count => managedItems.Count;

        public bool IsReadOnly => pointers.IsReadOnly;

        public void Add(T item) {
            managedItems.Add(item);
            pointers.Add(item.NativePtr);
        }

        public void Clear() {
            managedItems.Clear();
            pointers.Clear();
        }

        public bool Contains(T item) {
            return managedItems.Contains(item);
        }

        public void CopyTo(T[] array, int arrayIndex) {
            throw new NotImplementedException();
        }

        public IEnumerator<T> GetEnumerator() {
            return managedItems.GetEnumerator();
        }

        public int IndexOf(T item) {
            return managedItems.IndexOf(item);
        }

        public void Insert(int index, T item) {
            managedItems.Insert(index, item);
            pointers.Insert(index, item.NativePtr);
        }

        public bool Remove(T item) {
            pointers.Remove(item.NativePtr);
            return managedItems.Remove(item);
        }

        public void RemoveAt(int index) {
            pointers.RemoveAt(index);
            managedItems.RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return managedItems.GetEnumerator();
        }
    }
}
