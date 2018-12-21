using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics.Shader {
    public class Shader : Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Shader_new();

        protected override IntPtr NewObject() => Shader_new();


        public Shader() {
            FileName = "unnamed shader.hlsl";
        }

        public Shader(IntPtr ptr) : base(ptr) {
        }


        /*[DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern String Shader_getEntryPoint(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Shader_setEntryPoint(IntPtr _this, [MarshalAs(UnmanagedType.LPStr)] String entryPoint);

        public String EntryPoint {
            get {
                return Shader_getEntryPoint(NativePtr);
            }
            set {
                Shader_setEntryPoint(NativePtr, value);
            }
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern String Shader_getCompilationTarget(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Shader_setCompilationTarget(IntPtr _this, [MarshalAs(UnmanagedType.LPStr)] String compilationTarget);

        public String CompilationTarget {
            get {
                return Shader_getCompilationTarget(NativePtr);
            }
            set {
                Shader_setCompilationTarget(NativePtr, value);
            }
        }*/

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern String Shader_getSourceCode(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Shader_setSourceCode(IntPtr _this, [MarshalAs(UnmanagedType.LPStr)] String sourceCode);

        public String SourceCode {
            get {
                return Shader_getSourceCode(NativePtr);
            }
            set {
                Shader_setSourceCode(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern String Shader_compile(IntPtr _this);

        public String compile() => Shader_compile(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Shader_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Shader_getFormats());

    }
}
