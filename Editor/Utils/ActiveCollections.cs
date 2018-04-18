using System;
using System.Collections;
using System.Collections.Generic;

namespace Ghurund.Editor.Utils {
    public class ActiveListEventArgs<Type> : EventArgs {
        public Type Item { get; set; }
        public int Index { get; set; }

        public ActiveListEventArgs() {
        }

        public ActiveListEventArgs(Type item, int index) {
            Item = item;
            Index = index;
        }
    }

    public delegate void ActiveListEventHandler<Type>(object sender, ActiveListEventArgs<Type> e);

    public class ActiveList<Type> : List<Type> {
        public event ActiveListEventHandler<Type> ItemAdded;
        protected void OnItemAdded(ActiveListEventArgs<Type> args) {
            ItemAdded?.Invoke(this, args);
        }

        public new void Add(Type item) {
            base.Add(item);
            OnItemAdded(new ActiveListEventArgs<Type>(item, base.Count - 1));
        }

        public event ActiveListEventHandler<Type> ItemRemoved;
        protected void OnItemRemoved(ActiveListEventArgs<Type> args) {
            ItemRemoved?.Invoke(this, args);
        }

        public new void Remove(Type item) {
            int index = IndexOf(item);
            base.Remove(item);
            OnItemRemoved(new ActiveListEventArgs<Type>(item, index));
        }

        public event ActiveListEventHandler<Type> ItemSet;
        protected void OnItemSet(ActiveListEventArgs<Type> args) {
            ItemSet?.Invoke(this, args);
        }

        public new Type this[int index] {
            get {
                return base[index];
            }
            set {
                base[index] = value;
                OnItemSet(new ActiveListEventArgs<Type>(value, index));
            }
        }

    }

    public class ActiveDictionaryEventArgs<_Key, _Value> : EventArgs {
        public _Key Key { get; set; }
        public _Value Value { get; set; }

        public ActiveDictionaryEventArgs() {
        }

        public ActiveDictionaryEventArgs(_Key key, _Value value) {
            Key = key;
            Value = value;
        }
    }

    public delegate void ActiveDictionaryEventHandler<_Key, _Value>(object sender, ActiveDictionaryEventArgs<_Key, _Value> e);

    public class ActiveDictionary<Key, Value> : Dictionary<Key, Value> {
        public event ActiveDictionaryEventHandler<Key, Value> ItemAdded;
        protected void OnItemAdded(ActiveDictionaryEventArgs<Key, Value> args) {
            ItemAdded?.Invoke(this, args);
        }

        public new void Add(Key key, Value value) {
            base.Add(key, value);
            OnItemAdded(new ActiveDictionaryEventArgs<Key, Value>(key, value));
        }

        public event ActiveDictionaryEventHandler<Key, Value> ItemRemoved;
        protected void OnItemRemoved(ActiveDictionaryEventArgs<Key, Value> args) {
            ItemRemoved?.Invoke(this, args);
        }

        public new void Remove(Key key) {
            Value value = base[key];
            base.Remove(key);
            OnItemRemoved(new ActiveDictionaryEventArgs<Key, Value>(key, value));
        }
    }

    public class Pair<Type1, Type2> {
        public Type1 First { get; set; }
        public Type2 Second { get; set; }

        public Pair(Type1 f, Type2 s) {
            First = f;
            Second = s;
        }

        public override bool Equals(object obj) {
            return First.Equals(((Pair<Type1, Type2>)obj).First) &&
                   Second.Equals(((Pair<Type1, Type2>)obj).Second);
        }

        public override int GetHashCode() {
            return base.GetHashCode();
        }
    }

    public class DelegateControlCollectionEventArgs : EventArgs {
        public System.Windows.Forms.Control Item { get; set; }

        public DelegateControlCollectionEventArgs() {
        }

        public DelegateControlCollectionEventArgs(System.Windows.Forms.Control item) {
            Item = item;
        }
    }

    public delegate void DelegateControlCollectionEventHandler(object sender, DelegateControlCollectionEventArgs e);

    public class DelegateControlCollection {
        System.Windows.Forms.Control.ControlCollection collection;
        public DelegateControlCollection(System.Windows.Forms.Control.ControlCollection collection) {
            this.collection = collection;
        }

        public event DelegateControlCollectionEventHandler ItemAdded;
        protected void OnItemAdded(DelegateControlCollectionEventArgs args) {
            ItemAdded?.Invoke(this, args);
        }

        public void Add(System.Windows.Forms.Control item) {
            collection.Add(item);
            OnItemAdded(new DelegateControlCollectionEventArgs(item));
        }

        public event DelegateControlCollectionEventHandler ItemRemoved;
        protected void OnItemRemoved(DelegateControlCollectionEventArgs args) {
            ItemRemoved?.Invoke(this, args);
        }

        public void Remove(System.Windows.Forms.Control item) {
            collection.Remove(item);
            OnItemRemoved(new DelegateControlCollectionEventArgs(item));
        }

        public void Clear() {
            collection.Clear();
        }

        public bool Contains(System.Windows.Forms.Control item) {
            return collection.Contains(item);
        }

        public void CopyTo(System.Windows.Forms.Control[] dest, int index) {
            collection.CopyTo(dest, index);
        }

        public int Count {
            get {
                return collection.Count;
            }
        }

        public bool IsReadOnly {
            get {
                return collection.IsReadOnly;
            }
        }

        public IEnumerator GetEnumerator() {
            return collection.GetEnumerator();
        }
    }
}
