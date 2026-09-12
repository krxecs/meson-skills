# Windows and MSVC

This native MSVC-ABI example builds for the host platform with the Microsoft Visual C++ toolchain. For cross-compilation, use [cross-compilation](../cross-compilation/).

Shows a Windows-friendly DLL export pattern and a consumer executable.

On Windows, set up the compiler environment before configuring the build. On Visual Studio builds, Meson can use the VS backend or a native Ninja backend depending on the workflow.
