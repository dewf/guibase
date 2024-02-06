#include "../support/NativeImplServer.h"
#include "Windowing_wrappers.h"
#include "Windowing.h"
#include "Drawing_wrappers.h"

ni_ExceptionRef dropDataBadFormat;
ni_InterfaceMethodRef windowDelegate_canClose;
ni_InterfaceMethodRef windowDelegate_closed;
ni_InterfaceMethodRef windowDelegate_destroyed;
ni_InterfaceMethodRef windowDelegate_mouseDown;
ni_InterfaceMethodRef windowDelegate_mouseUp;
ni_InterfaceMethodRef windowDelegate_mouseMove;
ni_InterfaceMethodRef windowDelegate_mouseEnter;
ni_InterfaceMethodRef windowDelegate_mouseLeave;
ni_InterfaceMethodRef windowDelegate_repaint;
ni_InterfaceMethodRef windowDelegate_moved;
ni_InterfaceMethodRef windowDelegate_resized;
ni_InterfaceMethodRef windowDelegate_keyDown;
ni_InterfaceMethodRef windowDelegate_dropFeedback;
ni_InterfaceMethodRef windowDelegate_dropLeave;
ni_InterfaceMethodRef windowDelegate_dropSubmit;

inline void Key__push(Key value) {
    ni_pushInt32((int32_t)value);
}

inline Key Key__pop() {
    auto tag = ni_popInt32();
    return (Key)tag;
}

inline void Modifiers__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t Modifiers__pop() {
    return ni_popUInt32();
}

void Accelerator__push(Accelerator value) {
    ni_pushPtr(value);
}

Accelerator Accelerator__pop() {
    return (Accelerator)ni_popPtr();
}

void MenuActionFunc__push(std::function<MenuActionFunc> f) {
    size_t uniqueKey = 0;
    if (f) {
        MenuActionFunc* ptr_fun = f.target<MenuActionFunc>();
        if (ptr_fun != nullptr) {
            uniqueKey = (size_t)ptr_fun;
        }
    }
    auto wrapper = [f]() {
        f();
    };
    pushServerFuncVal(wrapper, uniqueKey);
}

std::function<MenuActionFunc> MenuActionFunc__pop() {
    auto id = ni_popClientFunc();
    auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
    auto wrapper = [cf]() {
        cf->remoteExec();
    };
    return wrapper;
}

void Action__push(Action value) {
    ni_pushPtr(value);
}

Action Action__pop() {
    return (Action)ni_popPtr();
}

void ClipData__push(ClipData value) {
    ni_pushPtr(value);
}

ClipData ClipData__pop() {
    return (ClipData)ni_popPtr();
}

inline void DropEffect__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t DropEffect__pop() {
    return ni_popUInt32();
}

// built-in array type: std::vector<std::string>

void DragRenderFunc__push(std::function<DragRenderFunc> f) {
    size_t uniqueKey = 0;
    if (f) {
        DragRenderFunc* ptr_fun = f.target<DragRenderFunc>();
        if (ptr_fun != nullptr) {
            uniqueKey = (size_t)ptr_fun;
        }
    }
    auto wrapper = [f]() {
        auto requestedFormat = popStringInternal();
        auto payload = DragRenderPayload__pop();
        ni_pushBool(f(requestedFormat, payload));
    };
    pushServerFuncVal(wrapper, uniqueKey);
}

std::function<DragRenderFunc> DragRenderFunc__pop() {
    auto id = ni_popClientFunc();
    auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
    auto wrapper = [cf](std::string requestedFormat, DragRenderPayload payload) {
        DragRenderPayload__push(payload);
        pushStringInternal(requestedFormat);
        cf->remoteExec();
        return ni_popBool();
    };
    return wrapper;
}

void DragData__push(DragData value) {
    ni_pushPtr(value);
}

DragData DragData__pop() {
    return (DragData)ni_popPtr();
}

inline void __Native_UInt8_Buffer__push(std::shared_ptr<NativeBuffer<uint8_t>> buf, bool isReturn) {
    if (buf != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(buf);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<NativeBuffer<uint8_t>> __Native_UInt8_Buffer__pop() {
    int id;
    bool isClientId;
    ni_BufferDescriptor descriptor;
    ni_popBuffer(&id, &isClientId, &descriptor);
    if (id != 0) {
        if (isClientId) {
            auto buf = new ClientBuffer<uint8_t>(id, descriptor);
            return std::shared_ptr<NativeBuffer<uint8_t>>(buf);
        }
        else {
            return ServerBuffer<uint8_t>::getByID(id);
        }
    }
    else {
        return std::shared_ptr<NativeBuffer<uint8_t>>();
    }
}

void DragRenderPayload__push(DragRenderPayload value) {
    ni_pushPtr(value);
}

DragRenderPayload DragRenderPayload__pop() {
    return (DragRenderPayload)ni_popPtr();
}


void DropDataBadFormat__push(DropDataBadFormat e) {
    pushStringInternal(e.format);
}

void DropDataBadFormat__buildAndThrow() {
    auto format = popStringInternal();
    throw DropDataBadFormat(format);
}

void DropData__push(DropData value) {
    ni_pushPtr(value);
}

DropData DropData__pop() {
    return (DropData)ni_popPtr();
}

void FileDialogResult__push(FileDialogResult value, bool isReturn) {
    pushStringArrayInternal(value.filenames);
    ni_pushBool(value.success);
}

FileDialogResult FileDialogResult__pop() {
    auto success = ni_popBool();
    auto filenames = popStringArrayInternal();
    return FileDialogResult { success, filenames };
}

inline void FileDialogMode__push(FileDialogMode value) {
    ni_pushInt32((int32_t)value);
}

inline FileDialogMode FileDialogMode__pop() {
    auto tag = ni_popInt32();
    return (FileDialogMode)tag;
}

void __String_Array_Array__push(std::vector<std::vector<std::string>> values, bool isReturn) {
    for (auto v = values.rbegin(); v != values.rend(); v++) {
        pushStringArrayInternal(*v);
    }
    ni_pushSizeT(values.size());
}

std::vector<std::vector<std::string>> __String_Array_Array__pop() {
    std::vector<std::vector<std::string>> __ret;
    auto count = ni_popSizeT();
    for (auto i = 0; i < count; i++) {
        auto value = popStringArrayInternal();
        __ret.push_back(value);
    }
    return __ret;
}

void FileDialogFilterSpec__push(FileDialogFilterSpec value, bool isReturn) {
    pushStringArrayInternal(value.extensions);
    pushStringInternal(value.description);
}

FileDialogFilterSpec FileDialogFilterSpec__pop() {
    auto description = popStringInternal();
    auto extensions = popStringArrayInternal();
    return FileDialogFilterSpec { description, extensions };
}

void __FileDialogFilterSpec_Array__push(std::vector<FileDialogFilterSpec> values, bool isReturn) {
    std::vector<std::vector<std::string>> extensions_values;
    std::vector<std::string> description_values;
    for (auto v = values.begin(); v != values.end(); v++) {
        extensions_values.push_back(v->extensions);
        description_values.push_back(v->description);
    }
    __String_Array_Array__push(extensions_values, isReturn);
    pushStringArrayInternal(description_values);
}

std::vector<FileDialogFilterSpec> __FileDialogFilterSpec_Array__pop() {
    auto description_values = popStringArrayInternal();
    auto extensions_values = __String_Array_Array__pop();
    std::vector<FileDialogFilterSpec> __ret;
    for (auto i = 0; i < description_values.size(); i++) {
        FileDialogFilterSpec __value;
        __value.description = description_values[i];
        __value.extensions = extensions_values[i];
        __ret.push_back(__value);
    }
    return __ret;
}

void FileDialogOptions__push(FileDialogOptions value, bool isReturn) {
    pushStringInternal(value.suggestedFilename);
    ni_pushBool(value.allowMultiple);
    pushStringInternal(value.defaultExt);
    ni_pushBool(value.allowAll);
    __FileDialogFilterSpec_Array__push(value.filters, isReturn);
    FileDialogMode__push(value.mode);
    Window__push(value.forWindow);
}

FileDialogOptions FileDialogOptions__pop() {
    auto forWindow = Window__pop();
    auto mode = FileDialogMode__pop();
    auto filters = __FileDialogFilterSpec_Array__pop();
    auto allowAll = ni_popBool();
    auto defaultExt = popStringInternal();
    auto allowMultiple = ni_popBool();
    auto suggestedFilename = popStringInternal();
    return FileDialogOptions { forWindow, mode, filters, allowAll, defaultExt, allowMultiple, suggestedFilename };
}

void FileDialog__push(FileDialog value) {
    ni_pushPtr(value);
}

FileDialog FileDialog__pop() {
    return (FileDialog)ni_popPtr();
}

void Icon__push(Icon value) {
    ni_pushPtr(value);
}

Icon Icon__pop() {
    return (Icon)ni_popPtr();
}

inline void KeyLocation__push(KeyLocation value) {
    ni_pushInt32((int32_t)value);
}

inline KeyLocation KeyLocation__pop() {
    auto tag = ni_popInt32();
    return (KeyLocation)tag;
}

void Menu__push(Menu value) {
    ni_pushPtr(value);
}

Menu Menu__pop() {
    return (Menu)ni_popPtr();
}

void MenuBar__push(MenuBar value) {
    ni_pushPtr(value);
}

MenuBar MenuBar__pop() {
    return (MenuBar)ni_popPtr();
}

void MenuItem__push(MenuItem value) {
    ni_pushPtr(value);
}

MenuItem MenuItem__pop() {
    return (MenuItem)ni_popPtr();
}

inline void MouseButton__push(MouseButton value) {
    ni_pushInt32((int32_t)value);
}

inline MouseButton MouseButton__pop() {
    auto tag = ni_popInt32();
    return (MouseButton)tag;
}

void TimerFunc__push(std::function<TimerFunc> f) {
    size_t uniqueKey = 0;
    if (f) {
        TimerFunc* ptr_fun = f.target<TimerFunc>();
        if (ptr_fun != nullptr) {
            uniqueKey = (size_t)ptr_fun;
        }
    }
    auto wrapper = [f]() {
        auto secondsSinceLast = ni_popDouble();
        f(secondsSinceLast);
    };
    pushServerFuncVal(wrapper, uniqueKey);
}

std::function<TimerFunc> TimerFunc__pop() {
    auto id = ni_popClientFunc();
    auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
    auto wrapper = [cf](double secondsSinceLast) {
        ni_pushDouble(secondsSinceLast);
        cf->remoteExec();
    };
    return wrapper;
}

void Timer__push(Timer value) {
    ni_pushPtr(value);
}

Timer Timer__pop() {
    return (Timer)ni_popPtr();
}


inline void WindowStyle__push(WindowStyle value) {
    ni_pushInt32((int32_t)value);
}

inline WindowStyle WindowStyle__pop() {
    auto tag = ni_popInt32();
    return (WindowStyle)tag;
}

void WindowOptions__push(WindowOptions value, bool isReturn) {
    size_t nativeParent;
    if (value.hasNativeParent(&nativeParent)) {
        ni_pushSizeT(nativeParent);
    }
    WindowStyle style;
    if (value.hasStyle(&style)) {
        WindowStyle__push(style);
    }
    int32_t maxHeight;
    if (value.hasMaxHeight(&maxHeight)) {
        ni_pushInt32(maxHeight);
    }
    int32_t maxWidth;
    if (value.hasMaxWidth(&maxWidth)) {
        ni_pushInt32(maxWidth);
    }
    int32_t minHeight;
    if (value.hasMinHeight(&minHeight)) {
        ni_pushInt32(minHeight);
    }
    int32_t minWidth;
    if (value.hasMinWidth(&minWidth)) {
        ni_pushInt32(minWidth);
    }
    ni_pushInt32(value.getUsedFields());
}

WindowOptions WindowOptions__pop() {
    WindowOptions value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & WindowOptions::Fields::MinWidthField) {
        auto x = ni_popInt32();
        value.setMinWidth(x);
    }
    if (value._usedFields & WindowOptions::Fields::MinHeightField) {
        auto x = ni_popInt32();
        value.setMinHeight(x);
    }
    if (value._usedFields & WindowOptions::Fields::MaxWidthField) {
        auto x = ni_popInt32();
        value.setMaxWidth(x);
    }
    if (value._usedFields & WindowOptions::Fields::MaxHeightField) {
        auto x = ni_popInt32();
        value.setMaxHeight(x);
    }
    if (value._usedFields & WindowOptions::Fields::StyleField) {
        auto x = WindowStyle__pop();
        value.setStyle(x);
    }
    if (value._usedFields & WindowOptions::Fields::NativeParentField) {
        auto x = ni_popSizeT();
        value.setNativeParent(x);
    }
    return value;
}

void Window__push(Window value) {
    ni_pushPtr(value);
}

Window Window__pop() {
    return (Window)ni_popPtr();
}

class ClientWindowDelegate : public ClientObject, public WindowDelegate {
public:
    ClientWindowDelegate(int id) : ClientObject(id) {}
    bool canClose() override {
        invokeMethod(windowDelegate_canClose);
        return ni_popBool();
    }
    void closed() override {
        invokeMethod(windowDelegate_closed);
    }
    void destroyed() override {
        invokeMethod(windowDelegate_destroyed);
    }
    void mouseDown(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) override {
        Modifiers__push(modifiers);
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_mouseDown);
    }
    void mouseUp(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) override {
        Modifiers__push(modifiers);
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_mouseUp);
    }
    void mouseMove(int32_t x, int32_t y, uint32_t modifiers) override {
        Modifiers__push(modifiers);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_mouseMove);
    }
    void mouseEnter(int32_t x, int32_t y, uint32_t modifiers) override {
        Modifiers__push(modifiers);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_mouseEnter);
    }
    void mouseLeave(uint32_t modifiers) override {
        Modifiers__push(modifiers);
        invokeMethod(windowDelegate_mouseLeave);
    }
    void repaint(DrawContext context, int32_t x, int32_t y, int32_t width, int32_t height) override {
        ni_pushInt32(height);
        ni_pushInt32(width);
        ni_pushInt32(y);
        ni_pushInt32(x);
        DrawContext__push(context);
        invokeMethod(windowDelegate_repaint);
    }
    void moved(int32_t x, int32_t y) override {
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_moved);
    }
    void resized(int32_t width, int32_t height) override {
        ni_pushInt32(height);
        ni_pushInt32(width);
        invokeMethod(windowDelegate_resized);
    }
    void keyDown(Key key, uint32_t modifiers, KeyLocation location) override {
        KeyLocation__push(location);
        Modifiers__push(modifiers);
        Key__push(key);
        invokeMethod(windowDelegate_keyDown);
    }
    uint32_t dropFeedback(DropData data, int32_t x, int32_t y, uint32_t modifiers, uint32_t suggested) override {
        DropEffect__push(suggested);
        Modifiers__push(modifiers);
        ni_pushInt32(y);
        ni_pushInt32(x);
        DropData__push(data);
        invokeMethod(windowDelegate_dropFeedback);
        return DropEffect__pop();
    }
    void dropLeave() override {
        invokeMethod(windowDelegate_dropLeave);
    }
    void dropSubmit(DropData data, int32_t x, int32_t y, uint32_t modifiers, uint32_t effect) override {
        DropEffect__push(effect);
        Modifiers__push(modifiers);
        ni_pushInt32(y);
        ni_pushInt32(x);
        DropData__push(data);
        invokeMethod(windowDelegate_dropSubmit);
    }
};

void WindowDelegate__push(std::shared_ptr<WindowDelegate> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<WindowDelegate> WindowDelegate__pop() {
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<WindowDelegate>(new ClientWindowDelegate(id));
        }
        else {
            return ServerWindowDelegate::getByID(id);
        }
    }
    else {
        return std::shared_ptr<WindowDelegate>();
    }
}

void moduleInit__wrapper() {
    moduleInit();
}

void moduleShutdown__wrapper() {
    moduleShutdown();
}

void runloop__wrapper() {
    runloop();
}

void exitRunloop__wrapper() {
    exitRunloop();
}

void DropData_hasFormat__wrapper() {
    auto _this = DropData__pop();
    auto mimeFormat = popStringInternal();
    ni_pushBool(DropData_hasFormat(_this, mimeFormat));
}

void DropData_getFiles__wrapper() {
    auto _this = DropData__pop();
    try {
        pushStringArrayInternal(DropData_getFiles(_this));
    }
    catch (const DropDataBadFormat& e) {
        ni_setException(dropDataBadFormat);
        DropDataBadFormat__push(e);
    }
}

void DropData_getTextUTF8__wrapper() {
    auto _this = DropData__pop();
    try {
        pushStringInternal(DropData_getTextUTF8(_this));
    }
    catch (const DropDataBadFormat& e) {
        ni_setException(dropDataBadFormat);
        DropDataBadFormat__push(e);
    }
}

void DropData_getFormat__wrapper() {
    auto _this = DropData__pop();
    auto mimeFormat = popStringInternal();
    try {
        __Native_UInt8_Buffer__push(DropData_getFormat(_this, mimeFormat), true);
    }
    catch (const DropDataBadFormat& e) {
        ni_setException(dropDataBadFormat);
        DropDataBadFormat__push(e);
    }
}

void DropData_dispose__wrapper() {
    auto _this = DropData__pop();
    DropData_dispose(_this);
}

void DragRenderPayload_renderUTF8__wrapper() {
    auto _this = DragRenderPayload__pop();
    auto text = popStringInternal();
    DragRenderPayload_renderUTF8(_this, text);
}

void DragRenderPayload_renderFiles__wrapper() {
    auto _this = DragRenderPayload__pop();
    auto filenames = popStringArrayInternal();
    DragRenderPayload_renderFiles(_this, filenames);
}

void DragRenderPayload_renderFormat__wrapper() {
    auto _this = DragRenderPayload__pop();
    auto formatMIME = popStringInternal();
    auto data = __Native_UInt8_Buffer__pop();
    DragRenderPayload_renderFormat(_this, formatMIME, data);
}

void DragRenderPayload_dispose__wrapper() {
    auto _this = DragRenderPayload__pop();
    DragRenderPayload_dispose(_this);
}

void DragData_dragExec__wrapper() {
    auto _this = DragData__pop();
    auto canDoMask = DropEffect__pop();
    DropEffect__push(DragData_dragExec(_this, canDoMask));
}

void DragData_create__wrapper() {
    auto supportedFormats = popStringArrayInternal();
    auto renderFunc = DragRenderFunc__pop();
    DragData__push(DragData_create(supportedFormats, renderFunc));
}

void DragData_dispose__wrapper() {
    auto _this = DragData__pop();
    DragData_dispose(_this);
}

void Window_show__wrapper() {
    auto _this = Window__pop();
    Window_show(_this);
}

void Window_showRelativeTo__wrapper() {
    auto _this = Window__pop();
    auto other = Window__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto newWidth = ni_popInt32();
    auto newHeight = ni_popInt32();
    Window_showRelativeTo(_this, other, x, y, newWidth, newHeight);
}

void Window_hide__wrapper() {
    auto _this = Window__pop();
    Window_hide(_this);
}

void Window_destroy__wrapper() {
    auto _this = Window__pop();
    Window_destroy(_this);
}

void Window_setMenuBar__wrapper() {
    auto _this = Window__pop();
    auto menuBar = MenuBar__pop();
    Window_setMenuBar(_this, menuBar);
}

void Window_showContextMenu__wrapper() {
    auto _this = Window__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto menu = Menu__pop();
    Window_showContextMenu(_this, x, y, menu);
}

void Window_invalidate__wrapper() {
    auto _this = Window__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    Window_invalidate(_this, x, y, width, height);
}

void Window_setTitle__wrapper() {
    auto _this = Window__pop();
    auto title = popStringInternal();
    Window_setTitle(_this, title);
}

void Window_enableDrops__wrapper() {
    auto _this = Window__pop();
    auto enable = ni_popBool();
    Window_enableDrops(_this, enable);
}

void Window_create__wrapper() {
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    auto title = popStringInternal();
    auto del = WindowDelegate__pop();
    auto opts = WindowOptions__pop();
    Window__push(Window_create(width, height, title, del, opts));
}

void Window_dispose__wrapper() {
    auto _this = Window__pop();
    Window_dispose(_this);
}

void Timer_create__wrapper() {
    auto msTimeout = ni_popInt32();
    auto func = TimerFunc__pop();
    Timer__push(Timer_create(msTimeout, func));
}

void Timer_dispose__wrapper() {
    auto _this = Timer__pop();
    Timer_dispose(_this);
}

void Icon_create__wrapper() {
    auto filename = popStringInternal();
    auto sizeToWidth = ni_popInt32();
    Icon__push(Icon_create(filename, sizeToWidth));
}

void Icon_dispose__wrapper() {
    auto _this = Icon__pop();
    Icon_dispose(_this);
}

void Accelerator_create__wrapper() {
    auto key = Key__pop();
    auto modifiers = Modifiers__pop();
    Accelerator__push(Accelerator_create(key, modifiers));
}

void Accelerator_dispose__wrapper() {
    auto _this = Accelerator__pop();
    Accelerator_dispose(_this);
}

void Action_create__wrapper() {
    auto label = popStringInternal();
    auto icon = Icon__pop();
    auto accel = Accelerator__pop();
    auto func = MenuActionFunc__pop();
    Action__push(Action_create(label, icon, accel, func));
}

void Action_dispose__wrapper() {
    auto _this = Action__pop();
    Action_dispose(_this);
}

void MenuItem_dispose__wrapper() {
    auto _this = MenuItem__pop();
    MenuItem_dispose(_this);
}

void Menu_addAction__wrapper() {
    auto _this = Menu__pop();
    auto action = Action__pop();
    MenuItem__push(Menu_addAction(_this, action));
}

void Menu_addSubmenu__wrapper() {
    auto _this = Menu__pop();
    auto label = popStringInternal();
    auto sub = Menu__pop();
    MenuItem__push(Menu_addSubmenu(_this, label, sub));
}

void Menu_addSeparator__wrapper() {
    auto _this = Menu__pop();
    Menu_addSeparator(_this);
}

void Menu_create__wrapper() {
    Menu__push(Menu_create());
}

void Menu_dispose__wrapper() {
    auto _this = Menu__pop();
    Menu_dispose(_this);
}

void MenuBar_addMenu__wrapper() {
    auto _this = MenuBar__pop();
    auto label = popStringInternal();
    auto menu = Menu__pop();
    MenuBar_addMenu(_this, label, menu);
}

void MenuBar_create__wrapper() {
    MenuBar__push(MenuBar_create());
}

void MenuBar_dispose__wrapper() {
    auto _this = MenuBar__pop();
    MenuBar_dispose(_this);
}

void ClipData_setClipboard__wrapper() {
    auto dragData = DragData__pop();
    ClipData_setClipboard(dragData);
}

void ClipData_get__wrapper() {
    ClipData__push(ClipData_get());
}

void ClipData_flushClipboard__wrapper() {
    ClipData_flushClipboard();
}

void ClipData_dispose__wrapper() {
    auto _this = ClipData__pop();
    ClipData_dispose(_this);
}

void FileDialog_openFile__wrapper() {
    auto opts = FileDialogOptions__pop();
    FileDialogResult__push(FileDialog_openFile(opts), true);
}

void FileDialog_saveFile__wrapper() {
    auto opts = FileDialogOptions__pop();
    FileDialogResult__push(FileDialog_saveFile(opts), true);
}

void FileDialog_dispose__wrapper() {
    auto _this = FileDialog__pop();
    FileDialog_dispose(_this);
}

void WindowDelegate_canClose__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    ni_pushBool(inst->canClose());
}

void WindowDelegate_closed__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->closed();
}

void WindowDelegate_destroyed__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->destroyed();
}

void WindowDelegate_mouseDown__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    auto modifiers = Modifiers__pop();
    inst->mouseDown(x, y, button, modifiers);
}

void WindowDelegate_mouseUp__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    auto modifiers = Modifiers__pop();
    inst->mouseUp(x, y, button, modifiers);
}

void WindowDelegate_mouseMove__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto modifiers = Modifiers__pop();
    inst->mouseMove(x, y, modifiers);
}

void WindowDelegate_mouseEnter__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto modifiers = Modifiers__pop();
    inst->mouseEnter(x, y, modifiers);
}

void WindowDelegate_mouseLeave__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto modifiers = Modifiers__pop();
    inst->mouseLeave(modifiers);
}

void WindowDelegate_repaint__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto context = DrawContext__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    inst->repaint(context, x, y, width, height);
}

void WindowDelegate_moved__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    inst->moved(x, y);
}

void WindowDelegate_resized__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    inst->resized(width, height);
}

void WindowDelegate_keyDown__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto key = Key__pop();
    auto modifiers = Modifiers__pop();
    auto location = KeyLocation__pop();
    inst->keyDown(key, modifiers, location);
}

void WindowDelegate_dropFeedback__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto data = DropData__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto modifiers = Modifiers__pop();
    auto suggested = DropEffect__pop();
    DropEffect__push(inst->dropFeedback(data, x, y, modifiers, suggested));
}

void WindowDelegate_dropLeave__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->dropLeave();
}

void WindowDelegate_dropSubmit__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto data = DropData__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto modifiers = Modifiers__pop();
    auto effect = DropEffect__pop();
    inst->dropSubmit(data, x, y, modifiers, effect);
}

void Windowing__constantsFunc() {
    pushStringInternal(kDragFormatFiles);
    pushStringInternal(kDragFormatUTF8);
}

int Windowing__register() {
    auto m = ni_registerModule("Windowing");
    ni_registerModuleConstants(m, &Windowing__constantsFunc);
    ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
    ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
    ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
    ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
    ni_registerModuleMethod(m, "DropData_hasFormat", &DropData_hasFormat__wrapper);
    ni_registerModuleMethod(m, "DropData_getFiles", &DropData_getFiles__wrapper);
    ni_registerModuleMethod(m, "DropData_getTextUTF8", &DropData_getTextUTF8__wrapper);
    ni_registerModuleMethod(m, "DropData_getFormat", &DropData_getFormat__wrapper);
    ni_registerModuleMethod(m, "DropData_dispose", &DropData_dispose__wrapper);
    ni_registerModuleMethod(m, "DragRenderPayload_renderUTF8", &DragRenderPayload_renderUTF8__wrapper);
    ni_registerModuleMethod(m, "DragRenderPayload_renderFiles", &DragRenderPayload_renderFiles__wrapper);
    ni_registerModuleMethod(m, "DragRenderPayload_renderFormat", &DragRenderPayload_renderFormat__wrapper);
    ni_registerModuleMethod(m, "DragRenderPayload_dispose", &DragRenderPayload_dispose__wrapper);
    ni_registerModuleMethod(m, "DragData_dragExec", &DragData_dragExec__wrapper);
    ni_registerModuleMethod(m, "DragData_create", &DragData_create__wrapper);
    ni_registerModuleMethod(m, "DragData_dispose", &DragData_dispose__wrapper);
    ni_registerModuleMethod(m, "Window_show", &Window_show__wrapper);
    ni_registerModuleMethod(m, "Window_showRelativeTo", &Window_showRelativeTo__wrapper);
    ni_registerModuleMethod(m, "Window_hide", &Window_hide__wrapper);
    ni_registerModuleMethod(m, "Window_destroy", &Window_destroy__wrapper);
    ni_registerModuleMethod(m, "Window_setMenuBar", &Window_setMenuBar__wrapper);
    ni_registerModuleMethod(m, "Window_showContextMenu", &Window_showContextMenu__wrapper);
    ni_registerModuleMethod(m, "Window_invalidate", &Window_invalidate__wrapper);
    ni_registerModuleMethod(m, "Window_setTitle", &Window_setTitle__wrapper);
    ni_registerModuleMethod(m, "Window_enableDrops", &Window_enableDrops__wrapper);
    ni_registerModuleMethod(m, "Window_create", &Window_create__wrapper);
    ni_registerModuleMethod(m, "Window_dispose", &Window_dispose__wrapper);
    ni_registerModuleMethod(m, "Timer_create", &Timer_create__wrapper);
    ni_registerModuleMethod(m, "Timer_dispose", &Timer_dispose__wrapper);
    ni_registerModuleMethod(m, "Icon_create", &Icon_create__wrapper);
    ni_registerModuleMethod(m, "Icon_dispose", &Icon_dispose__wrapper);
    ni_registerModuleMethod(m, "Accelerator_create", &Accelerator_create__wrapper);
    ni_registerModuleMethod(m, "Accelerator_dispose", &Accelerator_dispose__wrapper);
    ni_registerModuleMethod(m, "Action_create", &Action_create__wrapper);
    ni_registerModuleMethod(m, "Action_dispose", &Action_dispose__wrapper);
    ni_registerModuleMethod(m, "MenuItem_dispose", &MenuItem_dispose__wrapper);
    ni_registerModuleMethod(m, "Menu_addAction", &Menu_addAction__wrapper);
    ni_registerModuleMethod(m, "Menu_addSubmenu", &Menu_addSubmenu__wrapper);
    ni_registerModuleMethod(m, "Menu_addSeparator", &Menu_addSeparator__wrapper);
    ni_registerModuleMethod(m, "Menu_create", &Menu_create__wrapper);
    ni_registerModuleMethod(m, "Menu_dispose", &Menu_dispose__wrapper);
    ni_registerModuleMethod(m, "MenuBar_addMenu", &MenuBar_addMenu__wrapper);
    ni_registerModuleMethod(m, "MenuBar_create", &MenuBar_create__wrapper);
    ni_registerModuleMethod(m, "MenuBar_dispose", &MenuBar_dispose__wrapper);
    ni_registerModuleMethod(m, "ClipData_setClipboard", &ClipData_setClipboard__wrapper);
    ni_registerModuleMethod(m, "ClipData_get", &ClipData_get__wrapper);
    ni_registerModuleMethod(m, "ClipData_flushClipboard", &ClipData_flushClipboard__wrapper);
    ni_registerModuleMethod(m, "ClipData_dispose", &ClipData_dispose__wrapper);
    ni_registerModuleMethod(m, "FileDialog_openFile", &FileDialog_openFile__wrapper);
    ni_registerModuleMethod(m, "FileDialog_saveFile", &FileDialog_saveFile__wrapper);
    ni_registerModuleMethod(m, "FileDialog_dispose", &FileDialog_dispose__wrapper);
    auto windowDelegate = ni_registerInterface(m, "WindowDelegate");
    windowDelegate_canClose = ni_registerInterfaceMethod(windowDelegate, "canClose", &WindowDelegate_canClose__wrapper);
    windowDelegate_closed = ni_registerInterfaceMethod(windowDelegate, "closed", &WindowDelegate_closed__wrapper);
    windowDelegate_destroyed = ni_registerInterfaceMethod(windowDelegate, "destroyed", &WindowDelegate_destroyed__wrapper);
    windowDelegate_mouseDown = ni_registerInterfaceMethod(windowDelegate, "mouseDown", &WindowDelegate_mouseDown__wrapper);
    windowDelegate_mouseUp = ni_registerInterfaceMethod(windowDelegate, "mouseUp", &WindowDelegate_mouseUp__wrapper);
    windowDelegate_mouseMove = ni_registerInterfaceMethod(windowDelegate, "mouseMove", &WindowDelegate_mouseMove__wrapper);
    windowDelegate_mouseEnter = ni_registerInterfaceMethod(windowDelegate, "mouseEnter", &WindowDelegate_mouseEnter__wrapper);
    windowDelegate_mouseLeave = ni_registerInterfaceMethod(windowDelegate, "mouseLeave", &WindowDelegate_mouseLeave__wrapper);
    windowDelegate_repaint = ni_registerInterfaceMethod(windowDelegate, "repaint", &WindowDelegate_repaint__wrapper);
    windowDelegate_moved = ni_registerInterfaceMethod(windowDelegate, "moved", &WindowDelegate_moved__wrapper);
    windowDelegate_resized = ni_registerInterfaceMethod(windowDelegate, "resized", &WindowDelegate_resized__wrapper);
    windowDelegate_keyDown = ni_registerInterfaceMethod(windowDelegate, "keyDown", &WindowDelegate_keyDown__wrapper);
    windowDelegate_dropFeedback = ni_registerInterfaceMethod(windowDelegate, "dropFeedback", &WindowDelegate_dropFeedback__wrapper);
    windowDelegate_dropLeave = ni_registerInterfaceMethod(windowDelegate, "dropLeave", &WindowDelegate_dropLeave__wrapper);
    windowDelegate_dropSubmit = ni_registerInterfaceMethod(windowDelegate, "dropSubmit", &WindowDelegate_dropSubmit__wrapper);
    dropDataBadFormat = ni_registerException(m, "DropDataBadFormat", &DropDataBadFormat__buildAndThrow);
    return 0; // = OK
}
