﻿using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    class WCharStrMarshaler : ICustomMarshaler {
        public static ICustomMarshaler GetInstance(String cookie) {
            return new WCharStrMarshaler();
        }

        public void CleanUpManagedData(object ManagedObj) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void deleteArray(IntPtr obj);

        public void CleanUpNativeData(IntPtr pNativeData) {
            deleteArray(pNativeData);
        }

        public int GetNativeDataSize() {
            return IntPtr.Size;
        }

        public IntPtr MarshalManagedToNative(object ManagedObj) {
            throw new NotImplementedException();
        }

        public object MarshalNativeToManaged(IntPtr pNativeData) {
            return Marshal.PtrToStringUni(pNativeData);
        }
    }
}
