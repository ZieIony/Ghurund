using System.Drawing;
using System.Collections.Generic;
using System;

namespace Ghurund.Editor11{
	[Serializable]
	public class TokenClass {
		private Color color;
		public Color Color {
			get { return color; }
			set { color = value; }
		}

		private Font font;
		public Font Font {
			get { return font; }
			set { font = value; }
		}

		private List<String> tokenList;
		public List<String> TokenList {
			get { return tokenList; }
			set { tokenList = value; }
		}

        private Boolean caseSensitive;
        public System.Boolean CaseSensitive {
            get { return caseSensitive; }
            set { caseSensitive = value; }
        }

		public TokenClass() {
			tokenList = new List<String>();
			color = new Color();
			font = new Font("Microsoft Sans Serif", 8.25F, FontStyle.Regular, GraphicsUnit.Point, 238);
		}
	}
}