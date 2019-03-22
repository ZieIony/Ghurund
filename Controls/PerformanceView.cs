using System;
using System.Collections.Generic;
using System.Reactive.Linq;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls {
    public interface IPerformanceState {
        ulong getMax();
        ulong getMin();
        ulong getValue();
    }

    public class MemoryPerformanceState: IPerformanceState {
        public ulong getMax() {
            return new Microsoft.VisualBasic.Devices.ComputerInfo().TotalPhysicalMemory / (1024 * 1024);
        }

        public ulong getMin() {
            return 0;
        }

        public ulong getValue() {
            var computerInfo = new Microsoft.VisualBasic.Devices.ComputerInfo();
            return (computerInfo.TotalPhysicalMemory - computerInfo.AvailablePhysicalMemory) / (1024 * 1024);
        }

        public string getDescription() {
            return "" + getValue() + "/" + getMax() + "MB";
        }
    }

    public class PerformanceView: Control, IDisposable {
        IObservable<long> timer = Observable.Interval(TimeSpan.FromMilliseconds(1000));
        IDisposable timerSubscribtion;

        List<IPerformanceState> PerformanceStates = new List<IPerformanceState>();

        static PerformanceView() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PerformanceView), new FrameworkPropertyMetadata(typeof(PerformanceView)));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();

            var memoryUsage = GetTemplateChild("memory") as ProgressBar;

            timerSubscribtion = timer.Subscribe(tick => Dispatcher.Invoke(() => updateMemoryStatus()));
        }

        private void updateMemoryStatus() {
            //memoryUsage.Value = (computerInfo.TotalPhysicalMemory - computerInfo.AvailablePhysicalMemory) / (1024 * 1024);
            //memoryUsage.ToolTip = "" + memoryUsage.Value + "/" + memoryUsage.Maximum + "MB";
        }

        #region IDisposable Support
        private bool disposedValue = false;

        protected virtual void Dispose(bool disposing) {
            if (!disposedValue) {
                if (disposing) {
                    timerSubscribtion.Dispose();
                }

                disposedValue = true;
            }
        }

        public void Dispose() {
            Dispose(true);
        }
        #endregion
    }
}
