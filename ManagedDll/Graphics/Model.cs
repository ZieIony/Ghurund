using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Model : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_new();

        protected override void newObject() => NativePtr = Model_new();


        public Model() { }

        public Model(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getMesh(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setMesh(IntPtr _this, IntPtr mesh);

        public Mesh Mesh {
            get => new Mesh(Model_getMesh(NativePtr)); set => Model_setMesh(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Model_getMaterial(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Model_setMaterial(IntPtr _this, IntPtr mesh);

        public Material Material {
            get => new Material(Model_getMaterial(NativePtr)); set => Model_setMaterial(NativePtr, value.NativePtr);
        }

    }
}
