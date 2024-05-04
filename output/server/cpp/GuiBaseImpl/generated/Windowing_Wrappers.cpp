#include "../support/NativeImplServer.h"
#include "Windowing_wrappers.h"
#include "Windowing.h"

#include "Keys_wrappers.h"
using namespace Keys;

#include "Drawing_wrappers.h"
using namespace Drawing;

namespace Windowing
{
    // built-in array type: std::vector<std::string>
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
    void __FileDialog_FilterSpec_Array__push(std::vector<FileDialog::FilterSpec> values, bool isReturn) {
        std::vector<std::vector<std::string>> extensions_values;
        std::vector<std::string> description_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            extensions_values.push_back(v->extensions);
            description_values.push_back(v->description);
        }
        __String_Array_Array__push(extensions_values, isReturn);
        pushStringArrayInternal(description_values);
    }

    std::vector<FileDialog::FilterSpec> __FileDialog_FilterSpec_Array__pop() {
        auto description_values = popStringArrayInternal();
        auto extensions_values = __String_Array_Array__pop();
        std::vector<FileDialog::FilterSpec> __ret;
        for (auto i = 0; i < description_values.size(); i++) {
            FileDialog::FilterSpec __value;
            __value.description = description_values[i];
            __value.extensions = extensions_values[i];
            __ret.push_back(__value);
        }
        return __ret;
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
    void Modifiers__push(uint32_t value) {
        ni_pushUInt32(value);
    }

    uint32_t Modifiers__pop() {
        return ni_popUInt32();
    }
    void Icon__push(IconRef value) {
        ni_pushPtr(value);
    }

    IconRef Icon__pop() {
        return (IconRef)ni_popPtr();
    }
    namespace Icon {

        void create__wrapper() {
            auto filename = popStringInternal();
            auto sizeToWidth = ni_popInt32();
            Icon__push(create(filename, sizeToWidth));
        }
    }

    void Icon_dispose__wrapper() {
        auto _this = Icon__pop();
        Icon_dispose(_this);
    }
    void Accelerator__push(AcceleratorRef value) {
        ni_pushPtr(value);
    }

    AcceleratorRef Accelerator__pop() {
        return (AcceleratorRef)ni_popPtr();
    }
    namespace Accelerator {

        void create__wrapper() {
            auto key = Key__pop();
            auto modifiers = Modifiers__pop();
            Accelerator__push(create(key, modifiers));
        }
    }

    void Accelerator_dispose__wrapper() {
        auto _this = Accelerator__pop();
        Accelerator_dispose(_this);
    }
    void MenuAction__push(MenuActionRef value) {
        ni_pushPtr(value);
    }

    MenuActionRef MenuAction__pop() {
        return (MenuActionRef)ni_popPtr();
    }
    namespace MenuAction {
        void ActionFunc__push(std::function<ActionFunc> f) {
            size_t uniqueKey = 0;
            if (f) {
                ActionFunc* ptr_fun = f.target<ActionFunc>();
                if (ptr_fun != nullptr) {
                    uniqueKey = (size_t)ptr_fun;
                }
            }
            auto wrapper = [f]() {
                f();
            };
            pushServerFuncVal(wrapper, uniqueKey);
        }

        std::function<ActionFunc> ActionFunc__pop() {
            auto id = ni_popClientFunc();
            auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
            auto wrapper = [cf]() {
                cf->remoteExec();
            };
            return wrapper;
        }

        void create__wrapper() {
            auto label = popStringInternal();
            auto icon = Icon__pop();
            auto accel = Accelerator__pop();
            auto func = ActionFunc__pop();
            MenuAction__push(create(label, icon, accel, func));
        }
    }

    void MenuAction_dispose__wrapper() {
        auto _this = MenuAction__pop();
        MenuAction_dispose(_this);
    }
    void MenuItem__push(MenuItemRef value) {
        ni_pushPtr(value);
    }

    MenuItemRef MenuItem__pop() {
        return (MenuItemRef)ni_popPtr();
    }

    void MenuItem_dispose__wrapper() {
        auto _this = MenuItem__pop();
        MenuItem_dispose(_this);
    }
    void Menu__push(MenuRef value) {
        ni_pushPtr(value);
    }

    MenuRef Menu__pop() {
        return (MenuRef)ni_popPtr();
    }
    namespace Menu {

        void create__wrapper() {
            Menu__push(create());
        }
    }

    void Menu_addAction__wrapper() {
        auto _this = Menu__pop();
        auto action = MenuAction__pop();
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

    void Menu_dispose__wrapper() {
        auto _this = Menu__pop();
        Menu_dispose(_this);
    }
    void MenuBar__push(MenuBarRef value) {
        ni_pushPtr(value);
    }

    MenuBarRef MenuBar__pop() {
        return (MenuBarRef)ni_popPtr();
    }
    namespace MenuBar {

        void create__wrapper() {
            MenuBar__push(create());
        }
    }

    void MenuBar_addMenu__wrapper() {
        auto _this = MenuBar__pop();
        auto label = popStringInternal();
        auto menu = Menu__pop();
        MenuBar_addMenu(_this, label, menu);
    }

    void MenuBar_dispose__wrapper() {
        auto _this = MenuBar__pop();
        MenuBar_dispose(_this);
    }
    void DropData__push(DropDataRef value) {
        ni_pushPtr(value);
    }

    DropDataRef DropData__pop() {
        return (DropDataRef)ni_popPtr();
    }
    namespace DropData {
        ni_ExceptionRef badFormat;

        void BadFormat__push(BadFormat e) {
            pushStringInternal(e.format);
        }

        void BadFormat__buildAndThrow() {
            auto format = popStringInternal();
            throw BadFormat(format);
        }
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
        catch (const DropData::BadFormat& e) {
            ni_setException(DropData::badFormat);
            DropData::BadFormat__push(e);
        }
    }

    void DropData_getTextUTF8__wrapper() {
        auto _this = DropData__pop();
        try {
            pushStringInternal(DropData_getTextUTF8(_this));
        }
        catch (const DropData::BadFormat& e) {
            ni_setException(DropData::badFormat);
            DropData::BadFormat__push(e);
        }
    }

    void DropData_getFormat__wrapper() {
        auto _this = DropData__pop();
        auto mimeFormat = popStringInternal();
        try {
            __Native_UInt8_Buffer__push(DropData_getFormat(_this, mimeFormat), true);
        }
        catch (const DropData::BadFormat& e) {
            ni_setException(DropData::badFormat);
            DropData::BadFormat__push(e);
        }
    }

    void DropData_dispose__wrapper() {
        auto _this = DropData__pop();
        DropData_dispose(_this);
    }
    void DropEffect__push(uint32_t value) {
        ni_pushUInt32(value);
    }

    uint32_t DropEffect__pop() {
        return ni_popUInt32();
    }
    void DragData__push(DragDataRef value) {
        ni_pushPtr(value);
    }

    DragDataRef DragData__pop() {
        return (DragDataRef)ni_popPtr();
    }
    namespace DragData {
        void RenderPayload__push(RenderPayloadRef value) {
            ni_pushPtr(value);
        }

        RenderPayloadRef RenderPayload__pop() {
            return (RenderPayloadRef)ni_popPtr();
        }

        void RenderPayload_renderUTF8__wrapper() {
            auto _this = RenderPayload__pop();
            auto text = popStringInternal();
            RenderPayload_renderUTF8(_this, text);
        }

        void RenderPayload_renderFiles__wrapper() {
            auto _this = RenderPayload__pop();
            auto filenames = popStringArrayInternal();
            RenderPayload_renderFiles(_this, filenames);
        }

        void RenderPayload_renderFormat__wrapper() {
            auto _this = RenderPayload__pop();
            auto formatMIME = popStringInternal();
            auto data = __Native_UInt8_Buffer__pop();
            RenderPayload_renderFormat(_this, formatMIME, data);
        }

        void RenderPayload_dispose__wrapper() {
            auto _this = RenderPayload__pop();
            RenderPayload_dispose(_this);
        }
        void RenderFunc__push(std::function<RenderFunc> f) {
            size_t uniqueKey = 0;
            if (f) {
                RenderFunc* ptr_fun = f.target<RenderFunc>();
                if (ptr_fun != nullptr) {
                    uniqueKey = (size_t)ptr_fun;
                }
            }
            auto wrapper = [f]() {
                auto requestedFormat = popStringInternal();
                auto payload = RenderPayload__pop();
                ni_pushBool(f(requestedFormat, payload));
            };
            pushServerFuncVal(wrapper, uniqueKey);
        }

        std::function<RenderFunc> RenderFunc__pop() {
            auto id = ni_popClientFunc();
            auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
            auto wrapper = [cf](std::string requestedFormat, RenderPayloadRef payload) {
                RenderPayload__push(payload);
                pushStringInternal(requestedFormat);
                cf->remoteExec();
                return ni_popBool();
            };
            return wrapper;
        }

        void create__wrapper() {
            auto supportedFormats = popStringArrayInternal();
            auto renderFunc = RenderFunc__pop();
            DragData__push(create(supportedFormats, renderFunc));
        }
    }

    void DragData_dragExec__wrapper() {
        auto _this = DragData__pop();
        auto canDoMask = DropEffect__pop();
        DropEffect__push(DragData_dragExec(_this, canDoMask));
    }

    void DragData_dispose__wrapper() {
        auto _this = DragData__pop();
        DragData_dispose(_this);
    }
    void ClipData__push(ClipDataRef value) {
        ni_pushPtr(value);
    }

    ClipDataRef ClipData__pop() {
        return (ClipDataRef)ni_popPtr();
    }
    namespace ClipData {

        void setClipboard__wrapper() {
            auto dragData = DragData__pop();
            setClipboard(dragData);
        }

        void get__wrapper() {
            ClipData__push(get());
        }

        void flushClipboard__wrapper() {
            flushClipboard();
        }
    }

    void ClipData_dispose__wrapper() {
        auto _this = ClipData__pop();
        ClipData_dispose(_this);
    }
    void MouseButton__push(MouseButton value) {
        ni_pushInt32((int32_t)value);
    }

    MouseButton MouseButton__pop() {
        auto tag = ni_popInt32();
        return (MouseButton)tag;
    }
    static std::map<WindowDelegate*, std::weak_ptr<Pushable>> __windowDelegateToPushable;

    class ServerWindowDelegateWrapper : public ServerObject {
    public:
        std::shared_ptr<WindowDelegate> rawInterface;
    private:
        ServerWindowDelegateWrapper(std::shared_ptr<WindowDelegate> raw) {
            this->rawInterface = raw;
        }
        void releaseExtra() override {
            __windowDelegateToPushable.erase(rawInterface.get());
        }
    public:
        static std::shared_ptr<ServerWindowDelegateWrapper> wrapAndRegister(std::shared_ptr<WindowDelegate> raw) {
            auto ret = std::shared_ptr<ServerWindowDelegateWrapper>(new ServerWindowDelegateWrapper(raw));
            __windowDelegateToPushable[raw.get()] = ret;
            return ret;
        }
    };
    class ClientWindowDelegate : public ClientObject, public WindowDelegate {
    public:
        ClientWindowDelegate(int id) : ClientObject(id) {}
        ~ClientWindowDelegate() override {
            __windowDelegateToPushable.erase(this);
        }
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
        void repaint(DrawContextRef context, int32_t x, int32_t y, int32_t width, int32_t height) override {
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
        uint32_t dropFeedback(DropDataRef data, int32_t x, int32_t y, uint32_t modifiers, uint32_t suggested) override {
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
        void dropSubmit(DropDataRef data, int32_t x, int32_t y, uint32_t modifiers, uint32_t effect) override {
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
            auto found = __windowDelegateToPushable.find(inst.get());
            if (found != __windowDelegateToPushable.end()) {
                auto pushable = found->second.lock();
                pushable->push(pushable, isReturn);
            }
            else {
                auto pushable = ServerWindowDelegateWrapper::wrapAndRegister(inst);
                pushable->push(pushable, isReturn);
            }
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
                auto ret = std::shared_ptr<WindowDelegate>(new ClientWindowDelegate(id));
                __windowDelegateToPushable[ret.get()] = std::dynamic_pointer_cast<Pushable>(ret);
                return ret;
            }
            else {
                auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(id));
                return wrapper->rawInterface;
            }
        }
        else {
            return std::shared_ptr<WindowDelegate>();
        }
    }

    void WindowDelegate_canClose__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        ni_pushBool(inst->canClose());
    }

    void WindowDelegate_closed__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        inst->closed();
    }

    void WindowDelegate_destroyed__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        inst->destroyed();
    }

    void WindowDelegate_mouseDown__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto button = MouseButton__pop();
        auto modifiers = Modifiers__pop();
        inst->mouseDown(x, y, button, modifiers);
    }

    void WindowDelegate_mouseUp__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto button = MouseButton__pop();
        auto modifiers = Modifiers__pop();
        inst->mouseUp(x, y, button, modifiers);
    }

    void WindowDelegate_mouseMove__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto modifiers = Modifiers__pop();
        inst->mouseMove(x, y, modifiers);
    }

    void WindowDelegate_mouseEnter__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto modifiers = Modifiers__pop();
        inst->mouseEnter(x, y, modifiers);
    }

    void WindowDelegate_mouseLeave__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto modifiers = Modifiers__pop();
        inst->mouseLeave(modifiers);
    }

    void WindowDelegate_repaint__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto context = DrawContext__pop();
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto width = ni_popInt32();
        auto height = ni_popInt32();
        inst->repaint(context, x, y, width, height);
    }

    void WindowDelegate_moved__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        inst->moved(x, y);
    }

    void WindowDelegate_resized__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto width = ni_popInt32();
        auto height = ni_popInt32();
        inst->resized(width, height);
    }

    void WindowDelegate_keyDown__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto key = Key__pop();
        auto modifiers = Modifiers__pop();
        auto location = KeyLocation__pop();
        inst->keyDown(key, modifiers, location);
    }

    void WindowDelegate_dropFeedback__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto data = DropData__pop();
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto modifiers = Modifiers__pop();
        auto suggested = DropEffect__pop();
        DropEffect__push(inst->dropFeedback(data, x, y, modifiers, suggested));
    }

    void WindowDelegate_dropLeave__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        inst->dropLeave();
    }

    void WindowDelegate_dropSubmit__wrapper(int serverID) {
        auto wrapper = std::static_pointer_cast<ServerWindowDelegateWrapper>(ServerObject::getByID(serverID));
        auto inst = wrapper->rawInterface;
        auto data = DropData__pop();
        auto x = ni_popInt32();
        auto y = ni_popInt32();
        auto modifiers = Modifiers__pop();
        auto effect = DropEffect__pop();
        inst->dropSubmit(data, x, y, modifiers, effect);
    }
    void CursorStyle__push(CursorStyle value) {
        ni_pushInt32((int32_t)value);
    }

    CursorStyle CursorStyle__pop() {
        auto tag = ni_popInt32();
        return (CursorStyle)tag;
    }
    void Window__push(WindowRef value) {
        ni_pushPtr(value);
    }

    WindowRef Window__pop() {
        return (WindowRef)ni_popPtr();
    }
    namespace Window {
        void Style__push(Style value) {
            ni_pushInt32((int32_t)value);
        }

        Style Style__pop() {
            auto tag = ni_popInt32();
            return (Style)tag;
        }
        void Options__push(Options value, bool isReturn) {
            size_t nativeParent;
            if (value.hasNativeParent(&nativeParent)) {
                ni_pushSizeT(nativeParent);
            }
            Style style;
            if (value.hasStyle(&style)) {
                Style__push(style);
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

        Options Options__pop() {
            Options value = {};
            value._usedFields =  ni_popInt32();
            if (value._usedFields & Options::Fields::MinWidthField) {
                auto x = ni_popInt32();
                value.setMinWidth(x);
            }
            if (value._usedFields & Options::Fields::MinHeightField) {
                auto x = ni_popInt32();
                value.setMinHeight(x);
            }
            if (value._usedFields & Options::Fields::MaxWidthField) {
                auto x = ni_popInt32();
                value.setMaxWidth(x);
            }
            if (value._usedFields & Options::Fields::MaxHeightField) {
                auto x = ni_popInt32();
                value.setMaxHeight(x);
            }
            if (value._usedFields & Options::Fields::StyleField) {
                auto x = Style__pop();
                value.setStyle(x);
            }
            if (value._usedFields & Options::Fields::NativeParentField) {
                auto x = ni_popSizeT();
                value.setNativeParent(x);
            }
            return value;
        }

        void create__wrapper() {
            auto width = ni_popInt32();
            auto height = ni_popInt32();
            auto title = popStringInternal();
            auto del = WindowDelegate__pop();
            auto opts = Options__pop();
            Window__push(create(width, height, title, del, opts));
        }

        void mouseUngrab__wrapper() {
            mouseUngrab();
        }
    }

    void Window_destroy__wrapper() {
        auto _this = Window__pop();
        Window_destroy(_this);
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

    void Window_showModal__wrapper() {
        auto _this = Window__pop();
        auto parent = Window__pop();
        Window_showModal(_this, parent);
    }

    void Window_endModal__wrapper() {
        auto _this = Window__pop();
        Window_endModal(_this);
    }

    void Window_hide__wrapper() {
        auto _this = Window__pop();
        Window_hide(_this);
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

    void Window_focus__wrapper() {
        auto _this = Window__pop();
        Window_focus(_this);
    }

    void Window_mouseGrab__wrapper() {
        auto _this = Window__pop();
        Window_mouseGrab(_this);
    }

    void Window_getOSHandle__wrapper() {
        auto _this = Window__pop();
        ni_pushSizeT(Window_getOSHandle(_this));
    }

    void Window_enableDrops__wrapper() {
        auto _this = Window__pop();
        auto enable = ni_popBool();
        Window_enableDrops(_this, enable);
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

    void Window_setCursor__wrapper() {
        auto _this = Window__pop();
        auto style = CursorStyle__pop();
        Window_setCursor(_this, style);
    }

    void Window_dispose__wrapper() {
        auto _this = Window__pop();
        Window_dispose(_this);
    }
    void Timer__push(TimerRef value) {
        ni_pushPtr(value);
    }

    TimerRef Timer__pop() {
        return (TimerRef)ni_popPtr();
    }
    namespace Timer {
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

        void create__wrapper() {
            auto msTimeout = ni_popInt32();
            auto func = TimerFunc__pop();
            Timer__push(create(msTimeout, func));
        }
    }

    void Timer_dispose__wrapper() {
        auto _this = Timer__pop();
        Timer_dispose(_this);
    }
    namespace FileDialog {
        void Mode__push(Mode value) {
            ni_pushInt32((int32_t)value);
        }

        Mode Mode__pop() {
            auto tag = ni_popInt32();
            return (Mode)tag;
        }
        void FilterSpec__push(FilterSpec value, bool isReturn) {
            pushStringArrayInternal(value.extensions);
            pushStringInternal(value.description);
        }

        FilterSpec FilterSpec__pop() {
            auto description = popStringInternal();
            auto extensions = popStringArrayInternal();
            return FilterSpec { description, extensions };
        }
        void Options__push(Options value, bool isReturn) {
            pushStringInternal(value.suggestedFilename);
            ni_pushBool(value.allowMultiple);
            pushStringInternal(value.defaultExt);
            ni_pushBool(value.allowAll);
            __FileDialog_FilterSpec_Array__push(value.filters, isReturn);
            Mode__push(value.mode);
            Window__push(value.forWindow);
        }

        Options Options__pop() {
            auto forWindow = Window__pop();
            auto mode = Mode__pop();
            auto filters = __FileDialog_FilterSpec_Array__pop();
            auto allowAll = ni_popBool();
            auto defaultExt = popStringInternal();
            auto allowMultiple = ni_popBool();
            auto suggestedFilename = popStringInternal();
            return Options { forWindow, mode, filters, allowAll, defaultExt, allowMultiple, suggestedFilename };
        }
        void DialogResult__push(DialogResult value, bool isReturn) {
            pushStringArrayInternal(value.filenames);
            ni_pushBool(value.success);
        }

        DialogResult DialogResult__pop() {
            auto success = ni_popBool();
            auto filenames = popStringArrayInternal();
            return DialogResult { success, filenames };
        }

        void openFile__wrapper() {
            auto opts = Options__pop();
            DialogResult__push(openFile(opts), true);
        }

        void saveFile__wrapper() {
            auto opts = Options__pop();
            DialogResult__push(saveFile(opts), true);
        }
    }
    namespace MessageBoxModal {
        void Buttons__push(Buttons value) {
            ni_pushInt32((int32_t)value);
        }

        Buttons Buttons__pop() {
            auto tag = ni_popInt32();
            return (Buttons)tag;
        }
        void Icon__push(Icon value) {
            ni_pushInt32((int32_t)value);
        }

        Icon Icon__pop() {
            auto tag = ni_popInt32();
            return (Icon)tag;
        }
        void Params__push(Params value, bool isReturn) {
            Buttons__push(value.buttons);
            Icon__push(value.icon);
            ni_pushBool(value.withHelpButton);
            pushStringInternal(value.message);
            pushStringInternal(value.title);
        }

        Params Params__pop() {
            auto title = popStringInternal();
            auto message = popStringInternal();
            auto withHelpButton = ni_popBool();
            auto icon = Icon__pop();
            auto buttons = Buttons__pop();
            return Params { title, message, withHelpButton, icon, buttons };
        }
        void MessageBoxResult__push(MessageBoxResult value) {
            ni_pushInt32((int32_t)value);
        }

        MessageBoxResult MessageBoxResult__pop() {
            auto tag = ni_popInt32();
            return (MessageBoxResult)tag;
        }

        void show__wrapper() {
            auto forWindow = Window__pop();
            auto mbParams = Params__pop();
            MessageBoxResult__push(show(forWindow, mbParams));
        }
    }

    void __constantsFunc() {
        pushStringInternal(kDragFormatFiles);
        pushStringInternal(kDragFormatUTF8);
    }

    int __register() {
        auto m = ni_registerModule("Windowing");
        ni_registerModuleConstants(m, &__constantsFunc);
        ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
        ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
        ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
        ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
        ni_registerModuleMethod(m, "Icon_dispose", &Icon_dispose__wrapper);
        ni_registerModuleMethod(m, "Accelerator_dispose", &Accelerator_dispose__wrapper);
        ni_registerModuleMethod(m, "MenuAction_dispose", &MenuAction_dispose__wrapper);
        ni_registerModuleMethod(m, "MenuItem_dispose", &MenuItem_dispose__wrapper);
        ni_registerModuleMethod(m, "Menu_addAction", &Menu_addAction__wrapper);
        ni_registerModuleMethod(m, "Menu_addSubmenu", &Menu_addSubmenu__wrapper);
        ni_registerModuleMethod(m, "Menu_addSeparator", &Menu_addSeparator__wrapper);
        ni_registerModuleMethod(m, "Menu_dispose", &Menu_dispose__wrapper);
        ni_registerModuleMethod(m, "MenuBar_addMenu", &MenuBar_addMenu__wrapper);
        ni_registerModuleMethod(m, "MenuBar_dispose", &MenuBar_dispose__wrapper);
        ni_registerModuleMethod(m, "DropData_hasFormat", &DropData_hasFormat__wrapper);
        ni_registerModuleMethod(m, "DropData_getFiles", &DropData_getFiles__wrapper);
        ni_registerModuleMethod(m, "DropData_getTextUTF8", &DropData_getTextUTF8__wrapper);
        ni_registerModuleMethod(m, "DropData_getFormat", &DropData_getFormat__wrapper);
        ni_registerModuleMethod(m, "DropData_dispose", &DropData_dispose__wrapper);
        ni_registerModuleMethod(m, "DragData_dragExec", &DragData_dragExec__wrapper);
        ni_registerModuleMethod(m, "DragData_dispose", &DragData_dispose__wrapper);
        ni_registerModuleMethod(m, "ClipData_dispose", &ClipData_dispose__wrapper);
        ni_registerModuleMethod(m, "Window_destroy", &Window_destroy__wrapper);
        ni_registerModuleMethod(m, "Window_show", &Window_show__wrapper);
        ni_registerModuleMethod(m, "Window_showRelativeTo", &Window_showRelativeTo__wrapper);
        ni_registerModuleMethod(m, "Window_showModal", &Window_showModal__wrapper);
        ni_registerModuleMethod(m, "Window_endModal", &Window_endModal__wrapper);
        ni_registerModuleMethod(m, "Window_hide", &Window_hide__wrapper);
        ni_registerModuleMethod(m, "Window_invalidate", &Window_invalidate__wrapper);
        ni_registerModuleMethod(m, "Window_setTitle", &Window_setTitle__wrapper);
        ni_registerModuleMethod(m, "Window_focus", &Window_focus__wrapper);
        ni_registerModuleMethod(m, "Window_mouseGrab", &Window_mouseGrab__wrapper);
        ni_registerModuleMethod(m, "Window_getOSHandle", &Window_getOSHandle__wrapper);
        ni_registerModuleMethod(m, "Window_enableDrops", &Window_enableDrops__wrapper);
        ni_registerModuleMethod(m, "Window_setMenuBar", &Window_setMenuBar__wrapper);
        ni_registerModuleMethod(m, "Window_showContextMenu", &Window_showContextMenu__wrapper);
        ni_registerModuleMethod(m, "Window_setCursor", &Window_setCursor__wrapper);
        ni_registerModuleMethod(m, "Window_dispose", &Window_dispose__wrapper);
        ni_registerModuleMethod(m, "Timer_dispose", &Timer_dispose__wrapper);
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
        ni_registerModuleMethod(m, "Icon.create", &Icon::create__wrapper);
        ni_registerModuleMethod(m, "Accelerator.create", &Accelerator::create__wrapper);
        ni_registerModuleMethod(m, "MenuAction.create", &MenuAction::create__wrapper);
        ni_registerModuleMethod(m, "Menu.create", &Menu::create__wrapper);
        ni_registerModuleMethod(m, "MenuBar.create", &MenuBar::create__wrapper);
        DropData::badFormat = ni_registerException(m, "DropData.BadFormat", &DropData::BadFormat__buildAndThrow);
        ni_registerModuleMethod(m, "DragData.create", &DragData::create__wrapper);
        ni_registerModuleMethod(m, "DragData.RenderPayload_renderUTF8", &DragData::RenderPayload_renderUTF8__wrapper);
        ni_registerModuleMethod(m, "DragData.RenderPayload_renderFiles", &DragData::RenderPayload_renderFiles__wrapper);
        ni_registerModuleMethod(m, "DragData.RenderPayload_renderFormat", &DragData::RenderPayload_renderFormat__wrapper);
        ni_registerModuleMethod(m, "DragData.RenderPayload_dispose", &DragData::RenderPayload_dispose__wrapper);
        ni_registerModuleMethod(m, "ClipData.setClipboard", &ClipData::setClipboard__wrapper);
        ni_registerModuleMethod(m, "ClipData.get", &ClipData::get__wrapper);
        ni_registerModuleMethod(m, "ClipData.flushClipboard", &ClipData::flushClipboard__wrapper);
        ni_registerModuleMethod(m, "Window.create", &Window::create__wrapper);
        ni_registerModuleMethod(m, "Window.mouseUngrab", &Window::mouseUngrab__wrapper);
        ni_registerModuleMethod(m, "Timer.create", &Timer::create__wrapper);
        ni_registerModuleMethod(m, "FileDialog.openFile", &FileDialog::openFile__wrapper);
        ni_registerModuleMethod(m, "FileDialog.saveFile", &FileDialog::saveFile__wrapper);
        ni_registerModuleMethod(m, "MessageBoxModal.show", &MessageBoxModal::show__wrapper);
        return 0; // = OK
    }
}
