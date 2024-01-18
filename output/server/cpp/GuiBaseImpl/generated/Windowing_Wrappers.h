#include "Windowing.h"

void IWindow__push(std::shared_ptr<IWindow> inst, bool isReturn);
std::shared_ptr<IWindow> IWindow__pop();

void MouseButton__push(MouseButton value);
MouseButton MouseButton__pop();

void Modifiers__push(Modifiers value);
Modifiers Modifiers__pop();

void IWindowDelegate__push(std::shared_ptr<IWindowDelegate> inst, bool isReturn);
std::shared_ptr<IWindowDelegate> IWindowDelegate__pop();

void WindowStyle__push(WindowStyle value);
WindowStyle WindowStyle__pop();

void WindowOptions__push(WindowOptions value, bool isReturn);
WindowOptions WindowOptions__pop();

void moduleInit__wrapper();

void moduleShutdown__wrapper();

void runloop__wrapper();

void exitRunloop__wrapper();

void createWindow__wrapper();

void IWindowDelegate_canClose__wrapper(int serverID);

void IWindowDelegate_closed__wrapper(int serverID);

void IWindowDelegate_destroyed__wrapper(int serverID);

void IWindowDelegate_mouseDown__wrapper(int serverID);

void IWindowDelegate_repaint__wrapper(int serverID);

void IWindowDelegate_resized__wrapper(int serverID);

void IWindow_show__wrapper(int serverID);

void IWindow_destroy__wrapper(int serverID);

int Windowing__register();
