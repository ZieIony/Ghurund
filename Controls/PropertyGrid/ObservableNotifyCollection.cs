using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;

namespace Ghurund.Controls.PropertyGrid {
    public class ObservableNotifyCollection<T> : ObservableCollection<T> where T : INotifyPropertyChanged {
        public new void Add(T item) {
            base.Add(item);
            item.PropertyChanged += (object sender, PropertyChangedEventArgs e) => Refresh(item);
        }

        public void Refresh(int index) {
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, this[index], this[index], index));
        }

        public void Refresh(T item) {
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, item, item, IndexOf(item)));
        }
    }
}
