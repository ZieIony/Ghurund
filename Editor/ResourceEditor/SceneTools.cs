using Ghurund.Managed;
using Ghurund.Managed.Editor;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using System;

namespace Ghurund.Editor.ResourceEditor {

    public class CameraOrbitSceneTool: MouseSceneTool {
        private readonly RenderView renderView;

        public CameraOrbitSceneTool(RenderView renderView) {
            this.renderView = renderView;
        }

        public override bool OnMove(bool pressed, float dx, float dy) {
            if (!pressed)
                return false;
            renderView.Camera.Orbit((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
            return true;
        }

        public override void OnWheel(float dw) {
            renderView.Camera.Zoom(dw);
        }
    }

    public class CameraPanSceneTool: MouseSceneTool {
        private readonly RenderView renderView;

        public CameraPanSceneTool(RenderView renderView) {
            this.renderView = renderView;
        }

        public override bool OnMove(bool pressed, float dx, float dy) {
            if (!pressed)
                return false;
            renderView.Camera.Pan(dx, -dy);
            return true;
        }

        public override void OnWheel(float dw) {
            renderView.Camera.Zoom(dw);
        }
    }

    public class CameraZoomSceneTool: MouseSceneTool {
        private readonly RenderView renderView;

        public CameraZoomSceneTool(RenderView renderView) {
            this.renderView = renderView;
        }

        public override bool OnMove(bool pressed, float dx, float dy) {
            if (!pressed)
                return false;
            renderView.Camera.Zoom(dy);
            return true;
        }

        public override void OnWheel(float dw) {
            renderView.Camera.Zoom(dw);
        }
    }

    public class CameraRotateSceneTool: MouseSceneTool {
        private readonly RenderView renderView;

        public CameraRotateSceneTool(RenderView renderView) {
            this.renderView = renderView;
        }

        public override bool OnMove(bool pressed, float dx, float dy) {
            if (!pressed)
                return false;
            renderView.Camera.Rotate((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
            return true;
        }

        public override void OnWheel(float dw) {
            renderView.Camera.Zoom(dw);
        }
    }

    public class EntityMoveSceneTool: MouseSceneTool {
        private readonly RenderView renderView;
        private readonly System.Collections.Generic.List<Entity> selectedEntities;

        public EntityMoveSceneTool(RenderView renderView, System.Collections.Generic.List<Entity> selectedEntities) {
            this.renderView = renderView;
            this.selectedEntities = selectedEntities;
        }

        public override bool OnMove(bool pressed, float dx, float dy) {
            if (!pressed)
                return false;

            Float3 translateVector = CameraUtils.ScreenVectorTo3D(new Float2() { X = dx, Y = dy }, renderView.Camera);
            //                  if ()
            //                    translateVector.X = 0;
            foreach (Entity entity in selectedEntities) {
                if (entity is Model) {
                    Model model = entity as Model;
                    model.Position = new Float3(
                        model.Position.X + translateVector.X,
                        model.Position.Y + translateVector.Y,
                        model.Position.Z + translateVector.Z);
                }
            }

            return true;
        }
    }

}