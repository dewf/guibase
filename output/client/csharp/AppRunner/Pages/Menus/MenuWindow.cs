using static Org.Prefixed.GuiBase.Windowing;
using static Org.Prefixed.GuiBase.Drawing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages.Menus;

public class MenuWindow : BaseWindowDelegate
{
    private Window? _window;

    private MenuWindow()
    {
    }

    public static MenuWindow Create()
    {
        var ret = new MenuWindow();
        ret._window = Window.Create(200, 500, "", ret, new WindowOptions { Style = WindowStyle.Frameless });
        return ret;
    }
    public void ShowRelative(Window parentWindow, int x, int y)
    {
        _window!.ShowRelativeTo(parentWindow, x, y, 0, 0);
    }

    public override void Repaint(DrawContext context, int x, int y, int width, int height)
    {
        context.SetRGBFillColor(0.5, 0.5, 0.5, 1);
        context.FillRect(MakeRect(0, 0, 200, 500));
        
        context.SetRGBStrokeColor(0, 0, 0, 1);
        context.SetLineWidth(1);
        // context.StrokeRect(MakeRect(0, 0, 200, 500).Inset(0.5));
        context.MoveToPoint(0.5, 0);
        context.AddLineToPoint(0.5, 500-0.5);
        context.AddLineToPoint(200-0.5, 500-0.5);
        context.AddLineToPoint(200-0.5, 0);
        context.StrokePath();
    }
    
    public void Hide()
    {
        _window!.Hide();
    }
}
