using System;
using System.Collections.Immutable;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {

    public class Entity : NativeClass {

        public delegate void EntityChangeEventHandler(Object sender);
        public event EntityChangeEventHandler AfterChanged;

        public Entity() {
            initSubentities();
        }

        public Entity(IntPtr ptr) : base(ptr) {
            initSubentities();
        }

        protected void initSubentities() {
            Entity[] entities = new Entity[Entity_getSubentities_Size(NativePtr)];
            for (int i = 0; i < entities.Length; i++)
                entities[i] = new Entity(Entity_getSubentities_get(NativePtr, i));
            Subentities = ImmutableList.Create(entities);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Entity_getName(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setName(IntPtr _this, [MarshalAs(UnmanagedType.LPTStr)] String name);

        public String Name {
            get {
                return Entity_getName(NativePtr);
            }
            set {
                Entity_setName(NativePtr, value);
                AfterChanged?.Invoke(this);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Entity_getPosition(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setPosition(IntPtr _this, Float3 position);

        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Position {
            get {
                return Entity_getPosition(NativePtr);
            }
            set {
                Entity_setPosition(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Entity_getRotation(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setRotation(IntPtr _this, Float3 rotation);

        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Rotation {
            get {
                return Entity_getRotation(NativePtr);
            }
            set {
                Entity_setRotation(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Entity_getScale(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setScale(IntPtr _this, Float3 scale);

        [Description("Each value has to be > 0. For 100% scale use value = 1.0."),
             Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Scale {
            get {
                return Entity_getScale(NativePtr);
            }
            set {
                Entity_setScale(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Entity_getSubentities_Size(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getSubentities_get(IntPtr _this, int index);

        [Browsable(false)]
        public ImmutableList<Entity> Subentities {
            get; internal set;
        }

    }
}
