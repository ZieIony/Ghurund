using Ghurund.Managed.Resource;
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Script {
    public class Script: Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Script_new();

        protected override IntPtr NewObject() => Script_new();


        public Script() {
            FileName = "unnamed script.script";
        }

        public Script(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern string Script_getSourceCode(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Script_setSourceCode(IntPtr _this, [MarshalAs(UnmanagedType.LPStr)] string sourceCode);

        public string SourceCode {
            get => Script_getSourceCode(NativePtr);
            set => Script_setSourceCode(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern string Script_getEntryPoint(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Script_setEntryPoint(IntPtr _this, [MarshalAs(UnmanagedType.LPStr)] string sourceCode);

        public string EntryPoint {
            get => Script_getEntryPoint(NativePtr);
            set => Script_setEntryPoint(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern string Script_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ScriptEngine engine);

        public string Init(ScriptEngine engine) => Script_init(NativePtr, engine);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Script_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Script_getFormats(), ptr => new ResourceFormat(ptr));

    }
}
