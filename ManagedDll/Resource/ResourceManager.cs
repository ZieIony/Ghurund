using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceManager_new();

        public ResourceManager() {
            NativePtr = ResourceManager_new();
        }


        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void ResourceLoadedCallback(Status status);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadImage(IntPtr resourceManager, IntPtr context, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadImage(ResourceContext context, string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadImage(NativePtr, context.NativePtr, fileName, callback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadTexture(IntPtr resourceManager, IntPtr context, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadTexture(ResourceContext context, string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadTexture(NativePtr, context.NativePtr, fileName, callback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadMesh(IntPtr resourceManager, IntPtr context, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadMesh(ResourceContext context, string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadMesh(NativePtr, context.NativePtr, fileName, callback);
        }
    }
}
