using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;

namespace Ghurund.Controls.PropertyGrid {
    public class ObservableNotifyCollection<T> : ObservableCollection<T> where T : INotifyPropertyChanged {
        private Dictionary<T, PropertyChangedEventHandler> handlers = new Dictionary<T, PropertyChangedEventHandler>();

        public ObservableNotifyCollection() {
        }

        public new void Add(T item) {
            base.Add(item);
            var handler = new PropertyChangedEventHandler((object sender, PropertyChangedEventArgs e) => Refresh(item));
            handlers.Add(item, handler);
            item.PropertyChanged += handler;
        }

        protected override void RemoveItem(int index) {
            T item = this[index];
            item.PropertyChanged -= handlers[item];
            handlers.Remove(item);
            base.RemoveItem(index);
        }

        public new void Clear() {
            foreach(T item in this)
                item.PropertyChanged -= handlers[item];
            handlers.Clear();
            base.Clear();
        }

        public void Refresh(int index) {
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, this[index], this[index], index));
        }

        public void Refresh(T item) {
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, item, item, IndexOf(item)));
        }
    }
}
