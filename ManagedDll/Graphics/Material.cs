using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class Material : Resource.Resource {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_new();

        protected override void newObject() => NativePtr = Material_new();


        public Material() {
            FileName = "unnamed material.mtr";
        }

        public Material(IntPtr ptr) : base(ptr) {
        }


        public PipelineState PipelineState { get; set; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_getShader(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Material_setShader(IntPtr _this, IntPtr mesh);

        public Shader.Shader Shader{
            get => new Shader.Shader(Material_getShader(NativePtr)); set => Material_setShader(NativePtr, value.NativePtr);
        }

    }
}
