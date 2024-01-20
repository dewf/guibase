#include "Windowing.h"

void Accelerator__push(Accelerator value);
Accelerator Accelerator__pop();

void Action__push(Action value);
Action Action__pop();

void Icon__push(Icon value);
Icon Icon__pop();

void Key__push(Key value);
Key Key__pop();

void Menu__push(Menu value);
Menu Menu__pop();
void MenuActionFunc__push(std::function<MenuActionFunc> f);
std::function<MenuActionFunc> MenuActionFunc__pop();

void MenuBar__push(MenuBar value);
MenuBar MenuBar__pop();

void MenuItem__push(MenuItem value);
MenuItem MenuItem__pop();

void Modifiers__push(uint32_t value);
uint32_t Modifiers__pop();

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

void createIcon__wrapper();

void createAccelerator__wrapper();

void createAction__wrapper();

void createMenu__wrapper();

void createMenuBar__wrapper();

void Window_show__wrapper();

void Window_destroy__wrapper();

void Window_setMenuBar__wrapper();

void Window_showContextMenu__wrapper();

void Menu_addAction__wrapper();

void Menu_addSubmenu__wrapper();

void Menu_addSeparator__wrapper();

void MenuBar_addMenu__wrapper();

void WindowDelegate_canClose__wrapper(int serverID);

void WindowDelegate_closed__wrapper(int serverID);

void WindowDelegate_destroyed__wrapper(int serverID);

void WindowDelegate_mouseDown__wrapper(int serverID);

void WindowDelegate_repaint__wrapper(int serverID);

void WindowDelegate_resized__wrapper(int serverID);

int Windowing__register();
