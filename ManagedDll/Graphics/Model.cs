using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Model: Entity {
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
            get => new Mesh.Mesh(Model_getMesh(NativePtr));
            set => Model_setMesh(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getMaterial(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setMaterial(IntPtr _this, IntPtr mesh);

        public Material Material {
            get => new Material(Model_getMaterial(NativePtr)); set => Model_setMaterial(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Model_getPosition(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setPosition(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Three floats - x, y, z.")]
        [Controls.PropertyGrid.Editor(typeof(Float3PropertyEditor))]
        public Float3 Position {
            get => Model_getPosition(NativePtr);
            set => Model_setPosition(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Model_getRotation(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setRotation(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Euler angles - yaw, pitch, roll.")]
        [Controls.PropertyGrid.Editor(typeof(Float3PropertyEditor))]
        public Float3 Rotation {
            get => Model_getRotation(NativePtr);
            set => Model_setRotation(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Model_getScale(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setScale(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Scale 1 means 100%.")]
        [Controls.PropertyGrid.Editor(typeof(Float3PropertyEditor))]
        public Float3 Scale {
            get => Model_getScale(NativePtr);
            set => Model_setScale(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Model_getFormats(), ptr => new ResourceFormat(ptr));

    }

    public static class Models {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makeCube(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static Model MakeCube(ResourceContext context, Material material) {
            var entity = new Model(Models_makeCube(context, material));
            entity.Release();
            return entity;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makeCone(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static Model MakeCone(ResourceContext context, Material material) {
            var entity = new Model(Models_makeCone(context, material));
            entity.Release();
            return entity;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makePlane(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static Model MakePlane(ResourceContext context, Material material) {
            var entity = new Model(Models_makePlane(context, material));
            entity.Release();
            return entity;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Models_makeSphere(
                        [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext context,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material material);

        public static Model MakeSphere(ResourceContext context, Material material) {
            var entity = new Model(Models_makeSphere(context, material));
            entity.Release();
            return entity;
        }

    }
}
