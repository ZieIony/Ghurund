using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class DrawableComponent: Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponent_new();

        protected override IntPtr NewObject() => DrawableComponent_new();


        public DrawableComponent() { }

        public DrawableComponent(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponent_getMesh(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DrawableComponent_setMesh(IntPtr _this, IntPtr mesh);

        [Description("Mesh resource representing the geometry of this DrawableComponent.")]
        [Editable(true)]
        public Mesh.Mesh Mesh {
            get => new Mesh.Mesh(DrawableComponent_getMesh(NativePtr));
            set => DrawableComponent_setMesh(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponent_getMaterial(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DrawableComponent_setMaterial(IntPtr _this, IntPtr mesh);

        [Description("Material resource used for drawing this DrawableComponent.")]
        [Editable(true)]
        public Material Material {
            get => new Material(DrawableComponent_getMaterial(NativePtr)); set => DrawableComponent_setMaterial(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponent_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(DrawableComponent_getFormats(), ptr => new ResourceFormat(ptr));

    }

    public static class DrawableComponents {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponents_makeCube(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static DrawableComponent MakeCube(ResourceContext context, Material material) {
            var entity = new DrawableComponent(DrawableComponents_makeCube(context, material));
            entity.Release();
            return entity;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponents_makeCone(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static DrawableComponent MakeCone(ResourceContext context, Material material) {
            var entity = new DrawableComponent(DrawableComponents_makeCone(context, material));
            entity.Release();
            return entity;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponents_makePlane(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static DrawableComponent MakePlane(ResourceContext context, Material material) {
            var entity = new DrawableComponent(DrawableComponents_makePlane(context, material));
            entity.Release();
            return entity;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DrawableComponents_makeSphere(
                        [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static DrawableComponent MakeSphere(ResourceContext context, Material material) {
            var entity = new DrawableComponent(DrawableComponents_makeSphere(context, material));
            entity.Release();
            return entity;
        }
    }
}
