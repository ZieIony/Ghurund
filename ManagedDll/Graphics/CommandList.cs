using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class CommandList : NativeClass {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CommandList_new();

        protected override IntPtr NewObject() => CommandList_new();


        public CommandList() {
        }

        public CommandList(IntPtr ptr) : base(ptr) {
        }

    }
}