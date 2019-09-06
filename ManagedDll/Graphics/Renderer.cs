using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Collection;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Renderer : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_new();

        protected override IntPtr NewObject() => Renderer_new();


        public Renderer() {
        }

        public Renderer(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Renderer_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext);

        public void Init(ResourceContext resourceContext) {
            Renderer_init(NativePtr, resourceContext);
            Statistics = new RenderingStatistics(Renderer_getStatistics(NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_uninit(IntPtr _this);

        public void Uninit() {
            Renderer_uninit(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_setClearColor(IntPtr renderer, uint color);

        public uint ClearColor {
            set {
                Renderer_setClearColor(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_getStatistics(IntPtr renderer);

        public RenderingStatistics Statistics { get; private set; }
    }
}
