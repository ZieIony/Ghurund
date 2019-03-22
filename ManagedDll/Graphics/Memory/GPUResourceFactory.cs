using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics.Memory {
    public class GPUResourceFactory: NativeClass {
        public GPUResourceFactory(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))]
        private static extern ulong GPUResourceFactory_getSize(IntPtr _this);

        public ulong ResourceFactory => GPUResourceFactory_getSize(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))]
        private static extern ulong GPUResourceFactory_getAllocated(IntPtr _this);

        public ulong Allocated => GPUResourceFactory_getAllocated(NativePtr);
    }
}