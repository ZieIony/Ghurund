using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public abstract class NativeClass {
        private bool ptrOwner;

        [Browsable(false)]
        public IntPtr NativePtr { get; protected set; }

        protected virtual void newObject() { }

        public NativeClass() {
            newObject();
            ptrOwner = true;
        }

        public NativeClass(IntPtr ptr) {
            NativePtr = ptr;
            ptrOwner = false;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void deleteObject(IntPtr obj);

        ~NativeClass() {
            if (ptrOwner)
                deleteObject(NativePtr);
        }
    }
}