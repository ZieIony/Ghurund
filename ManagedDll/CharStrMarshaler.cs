using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    class CharStrMarshaler : ICustomMarshaler {
        public static ICustomMarshaler GetInstance(String cookie) {
            return new CharStrMarshaler();
        }

        public void CleanUpManagedData(object ManagedObj) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void deleteObject(IntPtr obj);

        public void CleanUpNativeData(IntPtr pNativeData) {
            deleteObject(pNativeData);
        }

        public int GetNativeDataSize() {
            return IntPtr.Size;
        }

        public IntPtr MarshalManagedToNative(object ManagedObj) {
            throw new NotImplementedException();
        }

        public object MarshalNativeToManaged(IntPtr pNativeData) {
            return Marshal.PtrToStringAnsi(pNativeData);
        }
    }
}
