﻿using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using Ghurund.Controls.Workspace;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {
    public interface ISceneEditor : IDockableControl {
        Scene Scene { get; set; }
    }

    public partial class SceneEditorPanel : UserControl, ISceneEditor, IStateControl {
        private Point prevPos;
        private bool pressed = false;

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        public SceneEditorPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);
        }

        private Scene scene;

        public Scene Scene {
            get => scene;
            set {
                scene = value;
                surfaceView.Scene = scene;
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public string Title { get => "Scene"; }

        public object Save() {
            return Scene?.FileName;
        }

        public void Restore(object state) {
            if (state != null) {
                string fileName = state as string;
                Scene = new Scene();
                Scene.Load(ResourceManager, ResourceContext, fileName);
            }
        }

        private void surfaceView_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e) {
            prevPos = new Point(e.X, e.Y);
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                pressed = true;
        }

        private void surfaceView_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (pressed) {
                var pos = new Point(e.X, e.Y);
                var dx = pos.X - prevPos.X;
                var dy = -(pos.Y - prevPos.Y);
                if (orbit.IsChecked.GetValueOrDefault(true)) {
                    surfaceView.Camera.Orbit((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                } else if (pan.IsChecked.GetValueOrDefault(true)) {
                    surfaceView.Camera.Pan((float)dx, (float)-dy);
                } else if (zoom.IsChecked.GetValueOrDefault(true)) {
                    surfaceView.Camera.Zoom((float)dy);
                } else {
                    surfaceView.Camera.Rotate((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                }
                surfaceView.Refresh();
                prevPos = pos;
            }
        }

        private void surfaceView_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                pressed = false;
        }

    }
}