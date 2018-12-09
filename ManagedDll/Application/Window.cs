using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Application {
    public class Window : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_new();


        public Window() {
            NativePtr = Window_new();
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_init(IntPtr _this, IntPtr handle);

        public void Init(IntPtr handle) {
            Window_init(NativePtr, handle);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_uninit(IntPtr _this);

        public void Uninit() {
            Window_uninit(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_updateSize(IntPtr _this);

        public void UpdateSize() {
            Window_updateSize(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterProvider_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager parameterManager) {
            ParameterProvider_initParameters(NativePtr, parameterManager.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterProvider_updateParameters(IntPtr _this);

        public void UpdateParameters() {
            ParameterProvider_updateParameters(NativePtr);
        }
    }
}
