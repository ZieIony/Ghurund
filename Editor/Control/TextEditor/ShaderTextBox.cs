using System;
using System.Drawing;
using Ghurund.Editor11;

namespace Ghurund.Editor.Control.TextEditor {
    public class ShaderTextBox : CodeTextBox {
        public ShaderTextBox() {
            TokenClass keywordClass = new TokenClass();
            keywordClass.CaseSensitive = false;
            keywordClass.Color = Color.Blue;
            keywordClass.Font = new Font("Consolas", 8.25F, FontStyle.Bold, GraphicsUnit.Point, 238);
            keywordClass.TokenList.AddRange(new String[]{"BlendState", "Bool", "Break", "Buffer","CBuffer", "Class", "Compile", "Const", "Continue",
                "DepthStencilState", "DepthStencilView", "Discard", "Do", "Double" ,
                "Else", "Extern"  ,
                "False", "Float", "For" ,
                "GeometryShader" ,
                "Half" ,
                "If", "In", "Inline" ,
                "Inout", "Int", "Interface"  ,
                "Matrix" ,
                "Namespace", "Nointerpolation" ,
                "Out",
                "Pass", "PixelShader", "Precise" ,
                "RasterizerState", "RenderTargetView", "Return", "Register" ,
                "Sampler", "Sampler1D", "Sampler2D", "Sampler3D", "SamplerCUBE", "Sampler_State", "SamplerComparisonState", "Shared", "Stateblock", "Stateblock_state", "Static", "String", "Struct", "Switch" ,
                "TBuffer", "Technique", "Technique10", "texture1", "Texture1D", "Texture1DArray", "Texture2D", "Texture2DArray", "Texture2DMS", "Texture2DMSArray", "Texture3D", "TextureCube", "TextureCubeArray", "True", "Typedef" ,
                "Uniform" ,
                "Vector", "VertexShader", "Void", "Volatile", "While"
            });
            TokenClasses.Add(keywordClass);
        }
    }
}
