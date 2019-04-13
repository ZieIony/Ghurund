using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Application;

namespace Ghurund.Managed.Graphics {
    public class SwapChain : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr SwapChain_new();

        protected override IntPtr NewObject() => SwapChain_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr SwapChain_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Graphics graphics,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Window window, uint frameCount);

        public void Init(Graphics graphics, Window window, uint frameCount) => SwapChain_init(NativePtr, graphics, window, frameCount);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr SwapChain_resize(IntPtr _this, uint width, uint height);

        public void Resize(uint width, uint height) => SwapChain_resize(NativePtr, width, height);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr SwapChain_getFrame(IntPtr _this);

        public IntPtr GetFrame() => SwapChain_getFrame(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SwapChain_present(IntPtr _this);

        public void Present() => SwapChain_present(NativePtr);
    }
}
