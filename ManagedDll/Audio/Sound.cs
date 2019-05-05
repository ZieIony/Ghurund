using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Audio {
    public class Sound : Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Sound_new();

        protected override IntPtr NewObject() => Sound_new();


        public Sound() {
        }

        public Sound(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Sound_play(IntPtr _this);

        public Status Play() => Sound_play(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Sound_stop(IntPtr _this);

        public void Stop() => Sound_stop(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Sound_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Sound_getFormats(), ptr => new ResourceFormat(ptr));

    }
}

