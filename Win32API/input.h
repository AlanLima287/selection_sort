#pragma once

#include <Windows.h>
#include <Windowsx.h>

#include "base.h"

namespace Win32API {

   class Input {

      friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

      class ButtonState {

         friend class Input;

      private:

         bool is_down, changed;

      public:

         ButtonState() :is_down(false), changed(false) {};

         ButtonState(const ButtonState&) = delete;
         ButtonState operator=(const ButtonState&) = delete;
         ~ButtonState() {};

         inline bool isDown() const { return is_down; }
         inline bool pressed() const { return is_down && changed; }
         inline bool released() const { return !is_down && changed; }
      };

      class KeyboardInput {

         friend class Input;

         static const uchar KEYBOARD_BUTTON_COUNT = 0xff;
         ButtonState keys[KEYBOARD_BUTTON_COUNT];

      public:

         inline bool isDown(uchar key) const { return keys[key].isDown(); }
         inline bool pressed(uchar key) const { return keys[key].pressed(); }
         inline bool released(uchar key) const { return keys[key].released(); }

      };

      typedef struct {
         ButtonState left, right, middle, x1_button, x2_button;
         int offsetX, offsetY, deltaX, deltaY, deltaWheel;
      } MouseInput;

   public:

      Input() {};
      Input(const Input&) = delete;
      Input operator=(const Input&) = delete;
      ~Input() {};

   public:

      MouseInput mouse;
      KeyboardInput keyboard;

   public:

      void processKeyboardInput(uchar vk_code, bool is_down) {
         keyboard.keys[vk_code].changed = is_down ^ keyboard.keys[vk_code].is_down;
         keyboard.keys[vk_code].is_down = is_down;
      }

      void processMouseInput(WPARAM wParam) {

         bool is_left_down = (wParam & MK_LBUTTON) != 0;
         bool is_right_down = (wParam & MK_RBUTTON) != 0;
         bool is_middle_down = (wParam & MK_MBUTTON) != 0;
         bool is_x1_button_down = (wParam & MK_XBUTTON1) != 0;
         bool is_x2_button_down = (wParam & MK_XBUTTON2) != 0;

         mouse.left.changed = mouse.left.is_down ^ is_left_down;
         mouse.right.changed = mouse.right.is_down ^ is_right_down;
         mouse.middle.changed = mouse.middle.is_down ^ is_middle_down;
         mouse.x2_button.changed = mouse.x2_button.is_down ^ is_x2_button_down;
         mouse.x1_button.changed = mouse.x1_button.is_down ^ is_x1_button_down;

         mouse.left.is_down = is_left_down;
         mouse.right.is_down = is_right_down;
         mouse.middle.is_down = is_middle_down;
         mouse.x2_button.is_down = is_x2_button_down;
         mouse.x1_button.is_down = is_x1_button_down;

      }

      void processMouseMovement(int xpos, int ypos) {

         mouse.deltaX = xpos - mouse.offsetX;
         mouse.deltaY = ypos - mouse.offsetY;

         mouse.offsetX = xpos;
         mouse.offsetY = ypos;
      }

      void processWheelMovement(short deltaWheel) {
         mouse.deltaWheel = deltaWheel;
      }

      void setChangedAttribute() {

         mouse.left.changed = false;
         mouse.right.changed = false;
         mouse.middle.changed = false;
         mouse.x1_button.changed = false;
         mouse.x2_button.changed = false;

         mouse.deltaX = 0;
         mouse.deltaY = 0;
         mouse.deltaWheel = 0;

         for (short i = 0; i < 0xff; i++) {
            keyboard.keys[i].changed = false;
         }
      }
   };
}
