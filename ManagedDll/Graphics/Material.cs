using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Material : Resource.Resource {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_new();

        protected override IntPtr NewObject() => Material_new();


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


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Material_getFormats());
    }

    public static class Materials {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeChecker(IntPtr resourceManager, IntPtr resourceContext);

        public static Material makeChecker(ResourceManager resourceManager, ResourceContext resourceContext) {
            return new Material(Materials_makeChecker(resourceManager.NativePtr, resourceContext.NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeWireframe(IntPtr resourceManager, IntPtr resourceContext);

        public static Material makeWireframe(ResourceManager resourceManager, ResourceContext resourceContext) {
            return new Material(Materials_makeWireframe(resourceManager.NativePtr, resourceContext.NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeNormals(IntPtr resourceManager, IntPtr resourceContext);

        public static Material makeNormals(ResourceManager resourceManager, ResourceContext resourceContext) {
            return new Material(Materials_makeNormals(resourceManager.NativePtr, resourceContext.NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeInvalid(IntPtr resourceManager, IntPtr resourceContext);

        public static Material makeInvalid(ResourceManager resourceManager, ResourceContext resourceContext) {
            return new Material(Materials_makeInvalid(resourceManager.NativePtr, resourceContext.NativePtr));
        }
    }
}
