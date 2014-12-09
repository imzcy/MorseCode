#ifndef _WIN32_MSVC_H_
#define _WIN32_MSVC_H_

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#ifdef _DEBUG
#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")
#pragma comment(lib, "Qt5SerialPortd.lib")
#pragma comment(lib, "libEGLd.lib")
#pragma comment(lib, "libGLESv2d.lib")
#else
#pragma comment(lib, "Qt5Core.lib")
#pragma comment(lib, "Qt5Gui.lib")
#pragma comment(lib, "Qt5Widgets.lib")
#pragma comment(lib, "Qt5SerialPort.lib")
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#endif // _DEBUG

#endif // _WIN32_MSVC_H_