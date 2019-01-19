using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    public class ParameterManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_new();

        protected override IntPtr NewObject() => ParameterManager_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint ParameterManager_getParameterCount(IntPtr _this);

        public uint ParameterCount {
            get => ParameterManager_getParameterCount(NativePtr);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_get(IntPtr _this, uint index);

        public Parameter Get(uint index) {
            return new Parameter(ParameterManager_get(NativePtr, index));
        }
    }
}
