using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public class Shader : NativeClass, IResource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Shader_new();

        public Shader() {
            NativePtr = Shader_new();
            FileName = "unnamed shader.hlsl";
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Shader_load(IntPtr _this, IntPtr resourceManager, [MarshalAs(UnmanagedType.LPTStr)] String fileName);

        public bool load(ResourceManager resourceManager, String fileName) {
            return Shader_load(NativePtr, resourceManager.NativePtr, fileName);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Shader_save(IntPtr _this, IntPtr resourceManager, [MarshalAs(UnmanagedType.LPTStr)] String fileName);

        public bool save(ResourceManager resourceManager, String fileName) {
            return Shader_save(NativePtr, resourceManager.NativePtr, fileName);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Shader_getFileName(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Shader_setFileName(IntPtr _this, [MarshalAs(UnmanagedType.LPTStr)] String fileName);

        public String FileName {
            get {
                return Shader_getFileName(NativePtr);
            }
            set {
                Shader_setFileName(NativePtr, value);
            }
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
        }

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
        }*/

        public string DefaultExtension {
            get {
                throw new NotImplementedException();
            }
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern String Shader_compile(IntPtr _this);

        public String compile() {
            return Shader_compile(NativePtr);
        }

    }
}
