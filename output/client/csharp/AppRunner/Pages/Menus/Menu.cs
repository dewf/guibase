using static Org.Prefixed.GuiBase.Windowing;
using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner.Pages.Menus;

public class Menu : BaseWindowDelegate
{
    private Window? _window;
    public static Menu Create(Window relativeTo, int x, int y)
    {
        var ret = new Menu();
        ret._window = Window.Create(200, 500, "", ret, new WindowOptions { Style = WindowStyle.Frameless });
        return ret;
    }
}
