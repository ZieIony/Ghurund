using Ghurund.Managed.Game;
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
        private static extern Status Script_build(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ScriptEngine engine);

        public Status Build(ScriptEngine engine) => Script_build(NativePtr, engine);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Script_execute(IntPtr _this);

        public Status Execute() => Script_execute(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Script_getFloatResult(IntPtr _this);

        public float GetFloatResult() => Script_getFloatResult(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Script_getFloat3Result(IntPtr _this);

        public Float3 GetFloat3Result() => Script_getFloat3Result(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Script_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Script_getFormats(), ptr => new ResourceFormat(ptr));

    }

    public static class Scripts {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Scripts_makeEmpty(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Entity param);

        public static Script MakeEmpty(Entity param) {
            var entity = new Script(Scripts_makeEmpty(param));
            entity.Release();
            return entity;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Scripts_make(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Entity param,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))] string sourceCode);

        public static Script Make(Entity param, string sourceCode) {
            var entity = new Script(Scripts_make(param, sourceCode));
            entity.Release();
            return entity;
        }
    }
}
