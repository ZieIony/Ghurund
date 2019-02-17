using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Application;
using Ghurund.Managed.Collection;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Renderer : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_new();

        protected override IntPtr NewObject() => Renderer_new();


        public Renderer() {
            Steps = new PointerList<RenderStep>(Renderer_getSteps(NativePtr), p => new RenderStep(p));
        }

        public Renderer(IntPtr ptr) : base(ptr) {
            Steps = new PointerList<RenderStep>(Renderer_getSteps(NativePtr), p => new RenderStep(p));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_getSteps(IntPtr _this);

        [Browsable(false)]
        public PointerList<RenderStep> Steps {
            get; internal set;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_init(IntPtr nativeRenderer, IntPtr window, IntPtr resourceManager, IntPtr resourceContext);

        public void Init(Window window, ResourceManager resourceManager, ResourceContext resourceContext) {
            Renderer_init(NativePtr, window.NativePtr, resourceManager.NativePtr, resourceContext.NativePtr);
            Statistics = new RenderingStatistics(Renderer_getStatistics(NativePtr));
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
        private static extern void Renderer_render(IntPtr nativeRenderer);

        public void Render() {
            Renderer_render(NativePtr);
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
