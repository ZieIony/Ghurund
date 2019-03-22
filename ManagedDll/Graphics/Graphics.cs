using Ghurund.Managed.Graphics.Memory;
using System;
using System.Collections.Immutable;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class Graphics: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Graphics_new();

        protected override IntPtr NewObject() => Graphics_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Graphics_init(IntPtr _this);

        public void Init() {
            Graphics_init(NativePtr);
            Adapter[] adapters = new Adapter[Graphics_getAdapters_Size(NativePtr)];
            for (int i = 0; i < adapters.Length; i++)
                adapters[i] = new Adapter(Graphics_getAdapters_get(NativePtr, i));
            Adapters = ImmutableList.Create(adapters);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Graphics_getAdapters_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Graphics_getAdapters_get(IntPtr _this, int index);

        [Browsable(false)]
        public ImmutableList<Adapter> Adapters {
            get; internal set;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))]
        private static extern IntPtr Graphics_getResourceFactory(IntPtr _this);

        public GPUResourceFactory ResourceFactory => new GPUResourceFactory(Graphics_getResourceFactory(NativePtr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reportLiveObjects();

    }
}
