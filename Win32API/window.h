#pragma once

#include <Windows.h>

#include "base.h"
#include "input.h"
#include "renderer.h"

namespace Win32API {

   class Window {

      friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

   private:

      HINSTANCE m_hInstance;
      HWND m_hWnd;
      HDC m_hDC;

      const LPCWSTR CLASS_NAME = (LPCWSTR)"Win32API Window";

      RenderState ctx;
      Input input;

      Window();

   public:

      Window(const Window&) = delete;
      Window operator=(const Window&) = delete;
      ~Window();

   public:

      inline static Window& getInstance() {
         static Window window;
         return window;
      }

      inline void setInstanceName(const char* window_name) {
         SetWindowTextW(m_hWnd, (LPCWSTR)window_name);
      }

      inline RenderState& getContext() { return ctx; }
      inline HDC getContextHandle() { return m_hDC; }

      inline Input& getInput() { return input; }

      void launchWindow(int = SW_NORMAL, bool = true, bool = true);
      bool windowProcess(float);

      void update(float);
      void resize();
   };
}