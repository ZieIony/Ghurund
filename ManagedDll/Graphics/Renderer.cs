using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Application;

namespace Ghurund.Managed.Graphics {
    public class Renderer : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_new();

        protected override IntPtr NewObject() => Renderer_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_init(IntPtr nativeRenderer, IntPtr graphics, IntPtr window);

        public void Init(Graphics graphics, Window window) {
            Renderer_init(NativePtr, graphics.NativePtr, window.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_startFrame(IntPtr nativeRenderer);

        public CommandList StartFrame() {
            return new CommandList(Renderer_startFrame(NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_finishFrame(IntPtr nativeRenderer);

        public void FinishFrame() {
            Renderer_finishFrame(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_uninit(IntPtr nativeRenderer);

        public void Uninit() {
            Renderer_uninit(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_resize(IntPtr nativeRenderer, uint width, uint height);

        public void Resize(uint width, uint height) {
            Renderer_resize(NativePtr, width, height);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_setMaterial(IntPtr nativeRenderer, IntPtr material);

        public Material Material {
            set {
                Renderer_setMaterial(NativePtr, value != null ? value.NativePtr : new IntPtr(0));
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_setInvalidMaterial(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Renderer _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public Material InvalidMaterial {
            set {
                Renderer_setInvalidMaterial(this, value);
            }
        }
    }
}
