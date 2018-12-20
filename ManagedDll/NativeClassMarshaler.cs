using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    class NativeClassMarshaler : ICustomMarshaler {
        public static ICustomMarshaler GetInstance(String cookie) {
            return new NativeClassMarshaler();
        }

        public void CleanUpManagedData(object ManagedObj) {
        }

        public void CleanUpNativeData(IntPtr pNativeData) {
        }

        public int GetNativeDataSize() {
            return IntPtr.Size;
        }

        public IntPtr MarshalManagedToNative(object ManagedObj) {
            return ManagedObj != null ? (ManagedObj as NativeClass).NativePtr : IntPtr.Zero;
        }

        public object MarshalNativeToManaged(IntPtr pNativeData) {
            throw new NotImplementedException();
        }
    }
}
