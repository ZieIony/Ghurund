using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Script {
    public class ScriptEngine: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ScriptEngine_new();

        protected override IntPtr NewObject() => ScriptEngine_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ScriptEngine_init(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Core.Timer timer);

        public void Init(Core.Timer timer) => ScriptEngine_init(NativePtr, timer);
    }
}

