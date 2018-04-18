using System.Collections.Generic;
using System.Windows.Forms;
using Ghurund.Editor.Utils;
using Ghurund.Managed.Game;

namespace Ghurund.Editor.Control.Outline {
    public partial class OutlinePanel : UserControl {
        public OutlinePanel() {
            InitializeComponent();
            Entities.ItemAdded += Entities_ItemAdded;

            treeView1.AfterSelect += TreeView1_AfterSelect;
        }

        private void TreeView1_AfterSelect(object sender, TreeViewEventArgs e) {
            SelectionChanged(this, new SelectionChangedEventArgs<EntityTreeNode>(treeView1.SelectedNode as EntityTreeNode));
        }

        public delegate void SelectionChangedEventHandler(System.Object sender, SelectionChangedEventArgs<EntityTreeNode> e);
        public event SelectionChangedEventHandler SelectionChanged;

        public ActiveList<Entity> Entities { get; } = new ActiveList<Entity>();

        private void Entities_ItemAdded(object sender, ActiveListEventArgs<Entity> e) {
            treeView1.Nodes.Add(new EntityTreeNode(e.Item));
        }

    }
}
