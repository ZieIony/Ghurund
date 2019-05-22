using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Material : Resource.Resource {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_new();

        protected override IntPtr NewObject() => Material_new();


        public Material() {
            FileName = "unnamed material.mtr";
            Parameters = new Array<Parameter>(Material_getParameters(NativePtr), p => new Parameter(p));
        }

        public Material(IntPtr ptr) : base(ptr) {
            Parameters = new Array<Parameter>(Material_getParameters(NativePtr), p => new Parameter(p));
        }


        public PipelineState PipelineState { get; set; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_getShader(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Material_setShader(IntPtr _this, IntPtr mesh);

        public Shader.Shader Shader {
            get => new Shader.Shader(Material_getShader(NativePtr));
            set => Material_setShader(NativePtr, value.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Material_getFormats(), ptr => new ResourceFormat(ptr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Material_getParameters(IntPtr _this);

        [Browsable(false)]
        public Array<Parameter> Parameters { get; private set; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Material_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager manager) {
            Material_initParameters(NativePtr, manager.NativePtr);
            Parameters = new Array<Parameter>(Material_getParameters(NativePtr), p => new Parameter(p));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Material_updateParameters(IntPtr _this);

        public void UpdateParameters() => Material_updateParameters(NativePtr);
    }

    public static class Materials {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeChecker(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext);

        public static Material MakeChecker(ResourceManager resourceManager, ResourceContext resourceContext) {
            Material material = new Material(Materials_makeChecker(resourceManager, resourceContext));
            material.Release();
            return material;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeWireframe(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext);

        public static Material MakeWireframe(ResourceManager resourceManager, ResourceContext resourceContext) {
            Material material = new Material(Materials_makeWireframe(resourceManager, resourceContext));
            material.Release();
            return material;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeNormals(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext);

        public static Material MakeNormals(ResourceManager resourceManager, ResourceContext resourceContext) {
            Material material = new Material(Materials_makeNormals(resourceManager, resourceContext));
            material.Release();
            return material;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Materials_makeInvalid(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceContext resourceContext);

        public static Material MakeInvalid(ResourceManager resourceManager, ResourceContext resourceContext) {
            Material material = new Material(Materials_makeInvalid(resourceManager, resourceContext));
            material.Release();
            return material;
        }
    }
}
