# GhurundEngine
My DirectX 12 playground.

##### Engine

It's written in C++ and HLSL. Uses DirectX 12 and WinAPI. One day I would also like to add a physics engine. It's a fourth iteration after one OpenGL engine, one DX9 and one DX11. I have a lot of ideas I would like to code, like support for resource hot reloading, automatic shader parameters, custom UI or keyframe animation system. I'm using a ton of VS features, so you won't be able to compile it with GCC.

##### Editor

Written in C# and WPF. Helps me verify my ideas and prepare assets quicker. It's also fun and stuff.

<img src='https://github.com/ZieIony/Ghurund/blob/master/images/editor.png' width=200/>

##### Preview

Made of the same blocks as Editor. Useful for polishing C++/C# interop and previewing resources.

##### Game

Not really a game right now. More like an app for checking if the engine is fine. This is how it looks like:

<img src='https://user-images.githubusercontent.com/10180628/39607596-228e5e8a-4f3c-11e8-8da2-b748510f7625.png' width=200/>

### Knowledge sources

##### Documentation and samples

 - [MSDN](https://msdn.microsoft.com/en-us/library/windows/desktop/dn899121(v=vs.85).aspx)
 - [samples and MiniEngine from Microsoft](https://github.com/Microsoft/DirectX-Graphics-Samples)
 - [GPUOpen Libraries & SDKs](https://github.com/GPUOpen-LibrariesAndSDKs)

##### Blogs and tutorials

 - [DirectX tutorials](https://www.braynzarsoft.net/viewtutorial/q16390-04-directx-12-braynzar-soft-tutorials)
 - [StarCraft II effects](https://developer.amd.com/wordpress/media/2012/10/S2008-Filion-McNaughton-StarCraftII.pdf)
 - [ReadDirectoryChangesW](https://qualapps.blogspot.com/2010/05/understanding-readdirectorychangesw_19.html)
 - [Lua tutorial](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-lua-tutorial-r2999/), [LuaBind tutorial](http://blog.nuclex-games.com/tutorials/cxx/luabind-introduction/)
 - [rendering techniques by Hiago DeSena (DX11)](https://www.hiagodesena.com/)
 - [gamma correct rendering](http://renderwonk.com/blog/index.php/archive/adventures-with-gamma-correct-rendering/), [linear space lighting](http://filmicworlds.com/blog/linear-space-lighting-i-e-gamma/)
 - [PBR](https://dirkiek.wordpress.com/2015/05/31/physically-based-rendering-and-image-based-lighting/)
 - [Self Shadow blog](http://blog.selfshadow.com/)

##### Books

 - [HLSL Development Cookbook](https://books.google.pl/books?id=lzxu6NGcFBQC&lpg=PP1&ots=w8RJiBlraM&dq=hlsl%20cookbook&hl=pl&pg=PP1#v=onepage&q&f=false)
 - [Real-Time 3D Rendering with DirectX and HLSL](https://books.google.pl/books?id=GY-AAwAAQBAJ&lpg=PA11&dq=directx%2012&hl=pl&pg=PP1#v=onepage&q&f=false)
 
### License

```
MIT License

Copyright (c) 2018 Marcin Korniluk 'Zielony'

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
