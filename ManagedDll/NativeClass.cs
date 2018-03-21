using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public abstract class NativeClass {
        public IntPtr NativePtr { get; protected set; }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void deleteObject(IntPtr obj);

        ~NativeClass() {
            deleteObject(NativePtr);
        }
    }
}