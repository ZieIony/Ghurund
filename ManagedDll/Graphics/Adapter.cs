using System;
using System.Collections.Immutable;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class DisplayMode : NativeClass {

        public DisplayMode(IntPtr ptr) {
            NativePtr = ptr;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint DisplayMode_getWidth(IntPtr _this);

        public uint Width {
            get {
                return DisplayMode_getWidth(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint DisplayMode_getHeight(IntPtr _this);

        public uint Height {
            get {
                return DisplayMode_getHeight(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float DisplayMode_getRefreshRate(IntPtr _this);

        public float RefreshRate {
            get {
                return DisplayMode_getRefreshRate(NativePtr);
            }
        }


        public override string ToString() {
            return Width + " x " + Height + ", " + RefreshRate + "Hz";
        }
    }

    public class AdapterOutput : NativeClass {

        public AdapterOutput(IntPtr ptr) {
            NativePtr = ptr;
            initDisplayModes();
        }

        protected void initDisplayModes() {
            DisplayMode[] displayModes = new DisplayMode[AdapterOutput_getDisplayModes_Size(NativePtr)];
            for (int i = 0; i < displayModes.Length; i++)
                displayModes[i] = new DisplayMode(AdapterOutput_getDisplayModes_get(NativePtr, i));
            DisplayModes = ImmutableList.Create(displayModes);
        }
        

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String AdapterOutput_getName(IntPtr _this);

        public String Name {
            get {
                return AdapterOutput_getName(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int AdapterOutput_getDisplayModes_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr AdapterOutput_getDisplayModes_get(IntPtr _this, int index);

        [Browsable(false)]
        public ImmutableList<DisplayMode> DisplayModes {
            get; internal set;
        }


        public override string ToString() {
            return Name;
        }
    }

    public class Adapter : NativeClass {

        public Adapter(IntPtr ptr) {
            NativePtr = ptr;
            initDisplayModes();
        }

        protected void initDisplayModes() {
            AdapterOutput[] adapterOutputs = new AdapterOutput[Adapter_getOutputs_Size(NativePtr)];
            for (int i = 0; i < adapterOutputs.Length; i++)
                adapterOutputs[i] = new AdapterOutput(Adapter_getOutputs_get(NativePtr, i));
            AdapterOutputs = ImmutableList.Create(adapterOutputs);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Adapter_getName(IntPtr _this);

        public String Name {
            get {
                return Adapter_getName(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Adapter_getDedicatedVideoMemory(IntPtr _this);

        public uint DedicatedVideoMemory {
            get {
                return Adapter_getDedicatedVideoMemory(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Adapter_getOutputs_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Adapter_getOutputs_get(IntPtr _this, int index);

        [Browsable(false)]
        public ImmutableList<AdapterOutput> AdapterOutputs {
            get; internal set;
        }


        public override string ToString() {
            return Name + " " + DedicatedVideoMemory / 1024 + "KB";
        }
    }
}