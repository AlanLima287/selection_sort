#pragma once

#include "window.h"

namespace Win32API {

   LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

      switch (uMsg) {

         case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

         case WM_DESTROY:
            PostQuitMessage(0);
            break;

         case WM_SYSKEYDOWN:
         case WM_SYSKEYUP:
         case WM_KEYDOWN:
         case WM_KEYUP: {

            uchar vkCode = (uchar)(wParam & 0xff);

            //bool wasDown = (lParam & 0x40000000) != 0;
            bool isDown = (lParam & 0x80000000) == 0;

            Window::getInstance().getInput().processKeyboardInput(vkCode, isDown);

         } break;

         case WM_LBUTTONUP:
         case WM_RBUTTONUP:
         case WM_MBUTTONUP:
         case WM_XBUTTONUP:
         case WM_LBUTTONDOWN:
         case WM_RBUTTONDOWN:
         case WM_MBUTTONDOWN:
         case WM_XBUTTONDOWN:
            Window::getInstance().getInput().processMouseInput(wParam);
            break;

         case WM_MOUSEMOVE: {

            int xpos = (int)((lParam) & 0xffff);
            int ypos = (int)((lParam >> 16) & 0xffff);

            Window::getInstance().getInput().processMouseMovement(xpos, ypos);

         } break;

         case WM_MOUSEWHEEL:
            Window::getInstance().getInput().processWheelMovement((short)((wParam >> 16) & 0xffff) / 120);
            break;

         case WM_SIZE: {

            RECT rect = {};
            GetClientRect(hWnd, &rect);

            ScreenToClient(hWnd, (POINT*)&rect);

            Window::getInstance().getContext().resizeWindowBuffer(rect, 1);
            //Window::getInstance().getContext().resizeWindowBuffer(rect.right, rect.bottom, 1);

            Window::getInstance().resize();

         } break;
      }

      return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }

   Window::Window() {

      WNDCLASSW wndClass = {};
      m_hInstance = {};

      wndClass.lpszClassName = CLASS_NAME;

      wndClass.style = CS_HREDRAW | CS_VREDRAW;
      wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
      wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

      wndClass.lpfnWndProc = WindowProcedure;
      wndClass.hInstance = m_hInstance;

      RegisterClassW(&wndClass);

      m_hWnd = CreateWindowExW(0,
         CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
         NULL, NULL, m_hInstance, NULL
      );

      m_hDC = GetDC(m_hWnd);
   }

   Window::~Window() {
      ReleaseDC(m_hWnd, m_hDC);
      UnregisterClassW(CLASS_NAME, m_hInstance);
   }

   void Window::launchWindow(int showMode, bool running, bool hideConsole) {

      ShowWindow(m_hWnd, showMode);

      if (hideConsole) FreeConsole();
      if (!running) return;

      float deltaTime = 0.0166666f;
      LARGE_INTEGER frameBeginTime, frameEndTime;
      QueryPerformanceCounter(&frameBeginTime);

      float performaceFrequency;
      {
         LARGE_INTEGER perf;
         QueryPerformanceFrequency(&perf);
         performaceFrequency = (float)perf.QuadPart;
      }

      while (windowProcess(deltaTime)) {
         QueryPerformanceCounter(&frameEndTime);
         deltaTime = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / performaceFrequency;
         frameBeginTime = frameEndTime;
      }
   }

   bool Window::windowProcess(float deltaTime) {
      
      input.setChangedAttribute();

      bool running = true;
      MSG msg = {};

      while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {

         if (msg.message == WM_QUIT) running = false;

         TranslateMessage(&msg);
         DispatchMessageW(&msg);

      }

      update(deltaTime);
      ctx.copyBufferToWindow(m_hDC);

      return running;
   }
}