#include "Windowing.h"

void Modifiers__push(Modifiers value);
Modifiers Modifiers__pop();

void MouseButton__push(MouseButton value);
MouseButton MouseButton__pop();

void Window__push(Window value);
Window Window__pop();

void WindowDelegate__push(std::shared_ptr<WindowDelegate> inst, bool isReturn);
std::shared_ptr<WindowDelegate> WindowDelegate__pop();

void WindowStyle__push(WindowStyle value);
WindowStyle WindowStyle__pop();

void WindowOptions__push(WindowOptions value, bool isReturn);
WindowOptions WindowOptions__pop();

void moduleInit__wrapper();

void moduleShutdown__wrapper();

void runloop__wrapper();

void exitRunloop__wrapper();

void createWindow__wrapper();

void Window_show__wrapper();

void Window_destroy__wrapper();

void WindowDelegate_canClose__wrapper(int serverID);

void WindowDelegate_closed__wrapper(int serverID);

void WindowDelegate_destroyed__wrapper(int serverID);

void WindowDelegate_mouseDown__wrapper(int serverID);

void WindowDelegate_repaint__wrapper(int serverID);

void WindowDelegate_resized__wrapper(int serverID);

int Windowing__register();
