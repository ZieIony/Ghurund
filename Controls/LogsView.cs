using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace Ghurund.Controls {
    public class LogsView : Control {

        public struct Log {
            public string Time { get; set; }
            public string Message { get; set; }
        }

        public ObservableCollection<Log> Logs { get; } = new ObservableCollection<Log>();

        private ICollectionView view;


        public string Filter {
            get { return (string)GetValue(FilterProperty); }
            set { SetValue(FilterProperty, value); }
        }

        public static readonly DependencyProperty FilterProperty =
            DependencyProperty.Register("Filter", typeof(string), typeof(LogsView), new PropertyMetadata(null));


        public bool AutoScroll {
            get { return (bool)GetValue(AutoScrollProperty); }
            set { SetValue(AutoScrollProperty, value); }
        }

        public static readonly DependencyProperty AutoScrollProperty =
            DependencyProperty.Register("AutoScroll", typeof(bool), typeof(LogsView), new PropertyMetadata(null));


        public bool WrapMessages {
            get { return (bool)GetValue(WrapMessagesProperty); }
            set { SetValue(WrapMessagesProperty, value); }
        }

        public static readonly DependencyProperty WrapMessagesProperty =
            DependencyProperty.Register("WrapMessages", typeof(bool), typeof(LogsView), new PropertyMetadata(null));


        static LogsView() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(LogsView), new FrameworkPropertyMetadata(typeof(LogsView)));
        }

        public LogsView() {
            view = CollectionViewSource.GetDefaultView(Logs);
            Logs.CollectionChanged += Logs_CollectionChanged;
        }

        private void Logs_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e) {
            if (AutoScroll)
                ScrollToBottom();
        }

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e) {
            base.OnPropertyChanged(e);
            if (e.Property == FilterProperty)
                view.Refresh();
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();

            view.Filter = obj => string.IsNullOrEmpty(Filter) ? true : (obj as string).ToLower().Contains(Filter);

            var listBox = GetTemplateChild("listBox") as ListBox;
            listBox.ItemsSource = view;
        }

        public void ScrollToBottom() {
            if (Logs.Count > 0) {
                var listBox = GetTemplateChild("listBox") as ListBox;
                listBox.ScrollIntoView(Logs[Logs.Count - 1]);
            }
        }
    }
}
