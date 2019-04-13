using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Graphics.Texture;
using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics.Mesh;

namespace Ghurund.Managed.Editor {
    public class ThumbnailRenderer: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_new();

        protected override IntPtr NewObject() => ThumbnailRenderer_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status ThumbnailRenderer_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext,
            uint width, uint height);

        public Status Init(ResourceManager resourceManager, ResourceContext resourceContext, uint width, uint height) {
            return ThumbnailRenderer_init(NativePtr, resourceManager, resourceContext, width, height);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_renderModel(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Model model);

        public Image Render(Model model) {
            return new Image(ThumbnailRenderer_renderModel(NativePtr, model));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_renderMesh(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Mesh mesh);

        public Image Render(Mesh mesh) {
            return new Image(ThumbnailRenderer_renderMesh(NativePtr, mesh));
        }
    }
}
