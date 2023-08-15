#include "DXHeader.h"
#include "Global.h"

map<MouseInput, bool> Input::Mouse;
Vector2 Input::MousePosition;
Raycast Input::MouseRaycast;
map<WPARAM, bool> Input::Key;
map<WPARAM, bool> Input::KeyHold;

void Input::InputBufferReset()
{
    for (int i = MouseInput::LBUTTONDOWN; i < MouseInput::END; ++i)
    {
        if (GetInputBuffer(Mouse, (MouseInput)i)) SetInputBuffer(Mouse, (MouseInput)i, false);
    }
    Key.clear();
}

void Input::InputBufferReset(bool p_Option)
{
    if (p_Option)
    {
        Mouse.clear();
        Key.clear();
        KeyHold.clear();
    }
    else
    {
        InputBufferReset();
    }
}
