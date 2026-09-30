# GhurundEngine
My DirectX 12 playground.

##### Engine

It's written in C++ and HLSL. Uses DirectX 12, PhysX and WinAPI.
It's a fourth iteration after one OpenGL engine, one DX9 and one DX11.

It was never meant to be the most performant - I'm more interested in writing clean, object-oriented code,
learning things, and just having fun. That's why Ghurund contains many small debug tools, and unit tests.
I wrote a couple of small games using Ghurund, but that's also not my goal. I enjoy programming in C++,
learning 3D graphics, physics, etc. It's really handy to have my own project for that,
that can be quickly set up to test certain things, like atmospheric scattering shaders.

I'm using WinAPI and MSVC-specific features in this project, so you won't be able to compile it with GCC nor run it without Windows.

##### Apps

 - Editor - the editor for Ghurund, wip.
 - Messenger - a simple text messenger using Ghurund's networking.
 - Preview - a simple resource viewer for Ghurund resources.

##### Samples

A couple of demos and samples, mostly for checking whether the project compiles and runs fine.

##### Tests

Unit tests for Ghurund features. Tests also include performance tests, compilation tests, and other tests that aren't really 'unit'.

##### Tools

 - BindingGenerator - generates bindings for UI widgets.
 - ShaderCompiler - compiles shader files using Ghurund to quickly validate shader code correctness.
 - SystemInfo - prints info about detected CPU, GPU, memory and display modes.

### Compilation

To build your own version you need the following tools:

 - [Visual Studio](https://visualstudio.microsoft.com/pl/vs/)
 - [Premake](https://premake.github.io/)
 - [DirectX 12](https://docs.microsoft.com/en-us/windows/desktop/direct3d12/directx-12-programming-environment-set-up)
 - [PhysX](https://github.com/NVIDIAGameWorks/PhysX)
 - [TinyXML-2](http://www.grinninglizard.com/tinyxml2)
 - [CRC](https://github.com/d-bahr/CRCpp)
 - [Box2D](https://github.com/erincatto/box2d)
 - [assimp](https://github.com/assimp/assimp)

### Knowledge sources

##### Documentation and samples

 - [PhysX](http://gameworksdocs.nvidia.com/simulation.html#physx)
 - [MSDN](https://msdn.microsoft.com/en-us/library/windows/desktop/dn899121(v=vs.85).aspx)
 - [samples and MiniEngine from Microsoft](https://github.com/Microsoft/DirectX-Graphics-Samples)
 - [GPUOpen Libraries & SDKs](https://github.com/GPUOpen-LibrariesAndSDKs)
 - [X3DAudio](https://docs.microsoft.com/en-us/windows/desktop/xaudio2/how-to--integrate-x3daudio-with-xaudio2)

##### Blogs and tutorials

 - [DirectX tutorials](https://www.braynzarsoft.net/viewtutorial/q16390-04-directx-12-braynzar-soft-tutorials)
 - [ReadDirectoryChangesW](https://qualapps.blogspot.com/2010/05/understanding-readdirectorychangesw_19.html)
 - [rendering techniques by Hiago DeSena (DX11)](https://www.hiagodesena.com/)
 - [gamma correct rendering](http://renderwonk.com/blog/index.php/archive/adventures-with-gamma-correct-rendering/), [linear space lighting](http://filmicworlds.com/blog/linear-space-lighting-i-e-gamma/)
 - [PBR](https://dirkiek.wordpress.com/2015/05/31/physically-based-rendering-and-image-based-lighting/), [PBR (OpenGL)](https://learnopengl.com/PBR/Lighting)
 - [Self Shadow blog](http://blog.selfshadow.com/)
 - [Making a Multiplayer FPS in C++](https://www.codersblock.org/blog/multiplayer-fps-part-1)

##### Books

 - [HLSL Development Cookbook](https://books.google.pl/books?id=lzxu6NGcFBQC&lpg=PP1&ots=w8RJiBlraM&dq=hlsl%20cookbook&hl=pl&pg=PP1#v=onepage&q&f=false)
 - [Real-Time 3D Rendering with DirectX and HLSL](https://books.google.pl/books?id=GY-AAwAAQBAJ&lpg=PA11&dq=directx%2012&hl=pl&pg=PP1#v=onepage&q&f=false)
 - [GPU Gems](https://developer.nvidia.com/gpugems/gpugems/contributors)
 
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
