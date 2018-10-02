using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceManager_new(IntPtr graphics, IntPtr audio, IntPtr parameterManager);

        public ResourceManager(Graphics.Graphics graphics, Audio.Audio audio, Game.ParameterManager parameterManager) {
            NativePtr = ResourceManager_new(graphics.NativePtr, audio.NativePtr, parameterManager.NativePtr);
        }


        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void ResourceLoadedCallback(Status status);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadImage(IntPtr resourceManager, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadImage(string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadImage(NativePtr, fileName, callback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadTexture(IntPtr resourceManager, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadTexture(string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadTexture(NativePtr, fileName, callback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceManager_loadModel(IntPtr resourceManager, string fileName,
            [MarshalAs(UnmanagedType.FunctionPtr)] ResourceLoadedCallback callback);

        public void LoadModel(string fileName, ResourceLoadedCallback callback) {
            ResourceManager_loadModel(NativePtr, fileName, callback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceManager_startLoading(IntPtr _this);

        public void StartLoading() {
            ResourceManager_startLoading(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceManager_finishLoading(IntPtr _this);

        public void FinishLoading() {
            ResourceManager_finishLoading(NativePtr);
        }
    }
}
