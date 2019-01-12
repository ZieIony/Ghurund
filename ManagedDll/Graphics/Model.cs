using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Model : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_new();

        protected override IntPtr NewObject() => Model_new();


        public Model() { }

        public Model(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getMesh(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setMesh(IntPtr _this, IntPtr mesh);

        public Mesh.Mesh Mesh {
            get => new Mesh.Mesh(Model_getMesh(NativePtr)); set => Model_setMesh(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getMaterial(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setMaterial(IntPtr _this, IntPtr mesh);

        public Material Material {
            get => new Material(Model_getMaterial(NativePtr)); set => Model_setMaterial(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Model_getFormats());

    }

    public static class Models {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makeCube(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static TransformedEntity MakeCube(ResourceContext context, Material material) {
            var entity = new TransformedEntity(Models_makeCube(context, material));
            entity.Release();
            return entity;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makePlane(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static TransformedEntity MakePlane(ResourceContext context, Material material) {
            var entity = new TransformedEntity(Models_makePlane(context, material));
            entity.Release();
            return entity;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makeSphere(
                        [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static TransformedEntity MakeSphere(ResourceContext context, Material material) {
            var entity = new TransformedEntity(Models_makeSphere(context, material));
            entity.Release();
            return entity;
        }

    }
}
