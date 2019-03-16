using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    internal static class NativeLists {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EntityList_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EntityList_add(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EntityList_insert(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EntityList_remove(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EntityList_removeAt(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EntityList_get(IntPtr _this, int index);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EntityList_set(IntPtr _this, int index, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EntityList_clear(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EntityList_contains(IntPtr _this, IntPtr item);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EntityList_indexOf(IntPtr _this, IntPtr item);
    }

    public class EntityList: NativeClass, IList<Entity>, INotifyCollectionChanged {

        private MakeNativeObjectDelegate<Entity> makeNativeObjectDelegate;

        public EntityList(IntPtr ptr, MakeNativeObjectDelegate<Entity> makeNativeObjectDelegate) : base(ptr) {
            this.makeNativeObjectDelegate = makeNativeObjectDelegate;
        }

        public Entity this[int index] {
            get => makeNativeObjectDelegate.Invoke(NativeLists.EntityList_get(NativePtr, index));
            set => NativeLists.EntityList_set(NativePtr, index, value.NativePtr);
        }

        public int Count => NativeLists.EntityList_Size(NativePtr);

        public bool IsReadOnly => false;

        public event NotifyCollectionChangedEventHandler CollectionChanged;

        public void Add(Entity item) {
            NativeLists.EntityList_add(NativePtr, item.NativePtr);
            CollectionChanged?.Invoke(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, item, Count - 1));
        }

        public void Clear() => NativeLists.EntityList_clear(NativePtr);

        public bool Contains(Entity item) => NativeLists.EntityList_contains(NativePtr, item.NativePtr);

        public void CopyTo(Entity[] array, int arrayIndex) => throw new NotImplementedException();

        public IEnumerator<Entity> GetEnumerator() => new ListEnumerator<Entity>(this);

        public int IndexOf(Entity item) => NativeLists.EntityList_indexOf(NativePtr, item.NativePtr);

        public void Insert(int index, Entity item) => NativeLists.EntityList_insert(NativePtr, index, item.NativePtr);

        public bool Remove(Entity item) => NativeLists.EntityList_remove(NativePtr, item.NativePtr);

        public void RemoveAt(int index) => NativeLists.EntityList_removeAt(NativePtr, index);

        IEnumerator IEnumerable.GetEnumerator() => new ListEnumerator<Entity>(this);
    }
}
