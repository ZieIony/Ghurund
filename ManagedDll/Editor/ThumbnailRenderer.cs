using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Graphics.Texture;
using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics.Mesh;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Editor {
    public class ThumbnailRenderer: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_new();

        protected override IntPtr NewObject() => ThumbnailRenderer_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status ThumbnailRenderer_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext,
            uint width, uint height);

        public Status Init(ResourceContext resourceContext, uint width, uint height) {
            return ThumbnailRenderer_init(NativePtr, resourceContext, width, height);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_renderEntity(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Entity entity);

        public Image Render(Entity entity) {
            return new Image(ThumbnailRenderer_renderEntity(NativePtr, entity));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_renderMesh(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Mesh mesh);

        public Image Render(Mesh mesh) {
            return new Image(ThumbnailRenderer_renderMesh(NativePtr, mesh));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ThumbnailRenderer_renderMaterial(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public Image Render(Material material) {
            return new Image(ThumbnailRenderer_renderMaterial(NativePtr, material));
        }
    }
}
