using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    internal static class NativeArrays {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Array_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Array_get(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Array_set(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Array_clear(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Array_contains(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Array_indexOf(IntPtr _this, IntPtr item);
    }

    public class PointerArray : IEnumerable<IntPtr>, IEnumerable {
        private readonly IntPtr ptr;

        public PointerArray(IntPtr ptr) {
            this.ptr = ptr;
        }

        public IntPtr this[int index] { get => NativeArrays.Array_get(ptr, index); set => NativeArrays.Array_set(ptr, index, value); }

        public int Count => NativeArrays.Array_Size(ptr);

        public bool IsReadOnly => false;

        public void Clear() {
            NativeArrays.Array_clear(ptr);
        }

        public bool Contains(IntPtr item) {
            return NativeArrays.Array_contains(ptr, item);
        }

        public void CopyTo(IntPtr[] array, int arrayIndex) {
            throw new NotImplementedException();
        }

        public IEnumerator<IntPtr> GetEnumerator() {
            throw new NotImplementedException();
        }

        public int IndexOf(IntPtr item) {
            return NativeArrays.Array_indexOf(ptr, item);
        }

        IEnumerator IEnumerable.GetEnumerator() {
            throw new NotImplementedException();
        }
    }

    public abstract class NativeArray<T> : IEnumerable, IEnumerable<T> where T : NativeClass {
        List<T> managedItems = new List<T>();
        PointerArray pointers;

        public NativeArray(IntPtr ptr) {
            pointers = new PointerArray(ptr);
            SyncArray();
        }

        public void SyncArray() {
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

        IEnumerator IEnumerable.GetEnumerator() {
            return managedItems.GetEnumerator();
        }
    }
}
