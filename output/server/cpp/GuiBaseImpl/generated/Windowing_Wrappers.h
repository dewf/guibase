#include "Windowing.h"

void Key__push(Key value);
Key Key__pop();

void Modifiers__push(uint32_t value);
uint32_t Modifiers__pop();

void Accelerator__push(Accelerator value);
Accelerator Accelerator__pop();
void MenuActionFunc__push(std::function<MenuActionFunc> f);
std::function<MenuActionFunc> MenuActionFunc__pop();

void Action__push(Action value);
Action Action__pop();

void ClipData__push(ClipData value);
ClipData ClipData__pop();

void DropEffect__push(uint32_t value);
uint32_t DropEffect__pop();
void DragRenderFunc__push(std::function<DragRenderFunc> f);
std::function<DragRenderFunc> DragRenderFunc__pop();

void DragData__push(DragData value);
DragData DragData__pop();

inline void __Native_UInt8_Buffer__push(std::shared_ptr<NativeBuffer<uint8_t>> buf, bool isReturn);
std::shared_ptr<NativeBuffer<uint8_t>> __Native_UInt8_Buffer__pop();

void DragRenderPayload__push(DragRenderPayload value);
DragRenderPayload DragRenderPayload__pop();

void DropDataBadFormat__push(DropDataBadFormat e);
void DropDataBadFormat__buildAndThrow();

void DropData__push(DropData value);
DropData DropData__pop();

void FileDialogResult__push(FileDialogResult value, bool isReturn);
FileDialogResult FileDialogResult__pop();

void FileDialogMode__push(FileDialogMode value);
FileDialogMode FileDialogMode__pop();

void FileDialogFilterSpec__push(FileDialogFilterSpec value, bool isReturn);
FileDialogFilterSpec FileDialogFilterSpec__pop();

void FileDialogOptions__push(FileDialogOptions value, bool isReturn);
FileDialogOptions FileDialogOptions__pop();

void FileDialog__push(FileDialog value);
FileDialog FileDialog__pop();

void Icon__push(Icon value);
Icon Icon__pop();

void KeyLocation__push(KeyLocation value);
KeyLocation KeyLocation__pop();

void Menu__push(Menu value);
Menu Menu__pop();

void MenuBar__push(MenuBar value);
MenuBar MenuBar__pop();

void MenuItem__push(MenuItem value);
MenuItem MenuItem__pop();

void MessageBoxButtons__push(MessageBoxButtons value);
MessageBoxButtons MessageBoxButtons__pop();

void MessageBoxIcon__push(MessageBoxIcon value);
MessageBoxIcon MessageBoxIcon__pop();

void MessageBoxResult__push(MessageBoxResult value);
MessageBoxResult MessageBoxResult__pop();

void MessageBoxParams__push(MessageBoxParams value, bool isReturn);
MessageBoxParams MessageBoxParams__pop();

void MessageBoxModal__push(MessageBoxModal value);
MessageBoxModal MessageBoxModal__pop();

void MouseButton__push(MouseButton value);
MouseButton MouseButton__pop();
void TimerFunc__push(std::function<TimerFunc> f);
std::function<TimerFunc> TimerFunc__pop();

void Timer__push(Timer value);
Timer Timer__pop();

void WindowStyle__push(WindowStyle value);
WindowStyle WindowStyle__pop();

void WindowOptions__push(WindowOptions value, bool isReturn);
WindowOptions WindowOptions__pop();

void Window__push(Window value);
Window Window__pop();

void WindowDelegate__push(std::shared_ptr<WindowDelegate> inst, bool isReturn);
std::shared_ptr<WindowDelegate> WindowDelegate__pop();

void moduleInit__wrapper();

void moduleShutdown__wrapper();

void runloop__wrapper();

void exitRunloop__wrapper();

void DropData_hasFormat__wrapper();

void DropData_getFiles__wrapper();

void DropData_getTextUTF8__wrapper();

void DropData_getFormat__wrapper();

void DropData_dispose__wrapper();

void DragRenderPayload_renderUTF8__wrapper();

void DragRenderPayload_renderFiles__wrapper();

void DragRenderPayload_renderFormat__wrapper();

void DragRenderPayload_dispose__wrapper();

void DragData_dragExec__wrapper();

void DragData_create__wrapper();

void DragData_dispose__wrapper();

void Window_show__wrapper();

void Window_showRelativeTo__wrapper();

void Window_hide__wrapper();

void Window_destroy__wrapper();

void Window_setMenuBar__wrapper();

void Window_showContextMenu__wrapper();

void Window_invalidate__wrapper();

void Window_setTitle__wrapper();

void Window_enableDrops__wrapper();

void Window_create__wrapper();

void Window_dispose__wrapper();

void Timer_create__wrapper();

void Timer_dispose__wrapper();

void Icon_create__wrapper();

void Icon_dispose__wrapper();

void Accelerator_create__wrapper();

void Accelerator_dispose__wrapper();

void Action_create__wrapper();

void Action_dispose__wrapper();

void MenuItem_dispose__wrapper();

void Menu_addAction__wrapper();

void Menu_addSubmenu__wrapper();

void Menu_addSeparator__wrapper();

void Menu_create__wrapper();

void Menu_dispose__wrapper();

void MenuBar_addMenu__wrapper();

void MenuBar_create__wrapper();

void MenuBar_dispose__wrapper();

void ClipData_setClipboard__wrapper();

void ClipData_get__wrapper();

void ClipData_flushClipboard__wrapper();

void ClipData_dispose__wrapper();

void FileDialog_openFile__wrapper();

void FileDialog_saveFile__wrapper();

void FileDialog_dispose__wrapper();

void MessageBoxModal_show__wrapper();

void MessageBoxModal_dispose__wrapper();

void WindowDelegate_canClose__wrapper(int serverID);

void WindowDelegate_closed__wrapper(int serverID);

void WindowDelegate_destroyed__wrapper(int serverID);

void WindowDelegate_mouseDown__wrapper(int serverID);

void WindowDelegate_mouseUp__wrapper(int serverID);

void WindowDelegate_mouseMove__wrapper(int serverID);

void WindowDelegate_mouseEnter__wrapper(int serverID);

void WindowDelegate_mouseLeave__wrapper(int serverID);

void WindowDelegate_repaint__wrapper(int serverID);

void WindowDelegate_moved__wrapper(int serverID);

void WindowDelegate_resized__wrapper(int serverID);

void WindowDelegate_keyDown__wrapper(int serverID);

void WindowDelegate_dropFeedback__wrapper(int serverID);

void WindowDelegate_dropLeave__wrapper(int serverID);

void WindowDelegate_dropSubmit__wrapper(int serverID);

void Windowing__constantsFunc();

int Windowing__register();
