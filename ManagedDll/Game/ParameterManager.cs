using Ghurund.Managed.Collection;
using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    public class ParameterManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_new();

        protected override IntPtr NewObject() => ParameterManager_new();


        public ParameterManager() {
            Parameters = new PointerList<Parameter>(ParameterManager_getParameters(NativePtr), p => new Parameter(p));
        }

        public ParameterManager(IntPtr ptr) : base(ptr) {
            Parameters = new PointerList<Parameter>(ParameterManager_getParameters(NativePtr), p => new Parameter(p));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_getParameters(IntPtr _this);

        public PointerList<Parameter> Parameters {
            get; internal set;
        }
    }
}
