using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public class Renderer : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_new();

        public Renderer() {
            NativePtr = Renderer_new();
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_init(IntPtr nativeRenderer, IntPtr graphics, IntPtr window);

        public void init(Graphics.Graphics graphics, Window window) {
            Renderer_init(NativePtr, graphics.NativePtr, window.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_startFrame(IntPtr nativeRenderer);

        public IntPtr startFrame() {
            return Renderer_startFrame(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_finishFrame(IntPtr nativeRenderer);

        public void finishFrame() {
            Renderer_finishFrame(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_uninit(IntPtr nativeRenderer);

        public void uninit() {
            Renderer_uninit(NativePtr);
        }
    }
}
