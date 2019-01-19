using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public delegate T MakeNativeObjectDelegate<T>(IntPtr p);

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

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getArrayItem(IntPtr array, int index);
    }

    public class ArrayEnumerator<T> : IEnumerator<T> where T : NativeClass {
        private readonly Array<T> array;
        private int index = -1;

        public ArrayEnumerator(Array<T> array) {
            this.array = array;
        }

        public T Current => array[index];

        object IEnumerator.Current => array[index];

        public void Dispose() {
        }

        public bool MoveNext() {
            index++;
            return index < array.Count;
        }

        public void Reset() {
            index = -1;
        }
    }

    public class Array<T> : NativeClass, IEnumerable, IEnumerable<T> where T : NativeClass {

        private MakeNativeObjectDelegate<T> makeNativeObjectDelegate;

        public Array(IntPtr ptr, MakeNativeObjectDelegate<T> makeNativeObjectDelegate) : base(ptr) {
            this.makeNativeObjectDelegate = makeNativeObjectDelegate;
        }

        public T this[int index] {
            get => makeNativeObjectDelegate.Invoke(NativeArrays.Array_get(NativePtr, index));
            set => NativeArrays.Array_set(NativePtr, index, value.NativePtr);
        }

        public int Count => NativeArrays.Array_Size(NativePtr);

        public bool IsReadOnly => false;

        public void Clear() => NativeArrays.Array_clear(NativePtr);

        public bool Contains(T item) => NativeArrays.Array_contains(NativePtr, item.NativePtr);

        public void CopyTo(T[] array, int arrayIndex) => throw new NotImplementedException();

        public IEnumerator<T> GetEnumerator() => new ArrayEnumerator<T>(this);

        public int IndexOf(T item) => NativeArrays.Array_indexOf(NativePtr, item.NativePtr);

        IEnumerator IEnumerable.GetEnumerator() => new ArrayEnumerator<T>(this);
    }
}
