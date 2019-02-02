using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public abstract class NativeClass : IDisposable {
        private bool disposed = false;
        protected readonly bool ptrOwner;

        [Browsable(false)]
        public IntPtr NativePtr { get; protected set; }

        protected virtual IntPtr NewObject() { return NativePtr; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Object_delete(IntPtr _this);

        protected virtual void DeleteObject() {
            if (ptrOwner)
                Object_delete(NativePtr);
        }

        public NativeClass() {
            NativePtr = NewObject();
            ptrOwner = true;
        }

        public NativeClass(IntPtr ptr) {
            NativePtr = ptr;
            ptrOwner = false;
        }

        ~NativeClass() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            DeleteObject();

            disposed = true;
        }

        public override bool Equals(object obj) {
            return obj != null && obj.GetType() == GetType() && NativePtr == (obj as NativeClass).NativePtr;
        }

        public override int GetHashCode() {
            return NativePtr.GetHashCode();
        }
    }
}