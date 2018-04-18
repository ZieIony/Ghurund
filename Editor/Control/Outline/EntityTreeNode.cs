using System.Windows.Forms;
using Ghurund.Managed.Game;

namespace Ghurund.Editor.Control.Outline {
    public class EntityTreeNode : TreeNode {
        public System.Boolean AllowDrag { get; set; }

        public System.Boolean AllowDrop { get; set; }

        public Entity Entity { get; }

        public EntityTreeNode() {
            AllowDrag = false;
            AllowDrop = false;
        }

        public EntityTreeNode(Entity entity) : base(entity.Name) {
            AllowDrag = false;
            AllowDrop = false;
            Entity = entity;
            Entity.AfterChanged += Entity_AfterChanged;
            foreach (Entity e in entity.Subentities)
                Nodes.Add(new EntityTreeNode(e));
        }

        private void Entity_AfterChanged(object sender) {
            Text = Entity.Name;
        }

        public override object Clone() {
            EntityTreeNode node = new EntityTreeNode();

            node.Text = Text;
            node.Name = Name;
            node.ImageIndex = ImageIndex;
            node.SelectedImageIndex = SelectedImageIndex;
            node.StateImageIndex = StateImageIndex;
            node.ToolTipText = ToolTipText;
            node.ContextMenu = ContextMenu;
            node.ContextMenuStrip = ContextMenuStrip;
            /*
			if (!string.IsNullOrEmpty(this.ImageIndex)) {
				node.ImageIndex = this.ImageIndex;
			}
			if (!string.IsNullOrEmpty(this.SelectedImageIndex)) {
				node.SelectedImageIndex = this.SelectedImageIndex;
			}
			if (!string.IsNullOrEmpty(this.StateImageIndex)) {
				node.StateImageIndex = this.StateImageIndex;
			}
			if (this.Nodes.Count > 0) {
				for (int i = 0; i < this.Nodes.Count; i++) {
					node.Nodes.Add((MovableTreeNode)this.Nodes[i].Clone());
				}
			}
			if (this.propBag != null) {
							node.propBag = OwnerDrawPropertyBag.Copy(this.propBag);
						}
						*/
            node.Checked = Checked;
            node.Tag = Tag;

            node.AllowDrag = AllowDrag;
            node.AllowDrop = AllowDrop;
            return node;
        }
    }
}
