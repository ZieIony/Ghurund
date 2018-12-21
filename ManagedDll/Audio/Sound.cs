using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Audio {
  public  class Sound : Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Sound_new();

        protected override IntPtr NewObject() => Sound_new();


        public Sound() {
        }

        public Sound(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Sound_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Sound_getFormats());

    }
}

