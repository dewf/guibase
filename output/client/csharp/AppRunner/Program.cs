using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;

namespace AppRunner;

internal class WindowHandler : ClientWindowDelegate
{
    private int _width, _height;
    private readonly Menu _contextMenu;
    public Window? Window { get; set; }
    
    public WindowHandler()
    {
        _contextMenu = CreateMenu();
        _contextMenu.AddAction(CreateAction("Context Item", null, null, () =>
        {
            Console.WriteLine("context item clicked!");
        }));
    }

    public override bool CanClose() => true;

    public override void Closed()
    {
        Console.WriteLine("window closed!!");
    }

    public override void Destroyed()
    {
        Console.WriteLine("window destroyed! exiting runloop");
        ExitRunloop();
    }

    public override void MouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
        if (button == MouseButton.Right)
        {
            Window!.ShowContextMenu(x, y, _contextMenu);
        }
    }
    private static string ModifiersToString(Modifiers modifiers)
    {
        var strings = 
            from modifier in new[] { Modifiers.Shift, Modifiers.Control, Modifiers.Alt, Modifiers.MacControl } where modifiers.HasFlag(modifier) select modifier.ToString();
        return string.Join("+", strings);
    }
    public override void Repaint(DrawContext context, int x, int y, int width, int height)
    {
        context.SaveGState();
        
        // bordered
        context.SetRGBFillColor(0.23, 0, 0.4, 1);
        context.FillRect(new Rect(new Point(10, 10), new Size(_width - 20, _height - 20)));

        // overlapping
        var rect = new Rect(new Point(100, 100), new Size(100, 100));
        context.SetRGBFillColor(1, 0, 0, 0.5);
        context.FillRect(rect);

        rect.Origin.X += 20;
        rect.Origin.Y += 20;
        context.SetRGBFillColor(0, 1, 0, 0.5);
        context.FillRect(rect);
        
        rect.Origin.X += 20;
        rect.Origin.Y += 20;
        context.SetRGBFillColor(0, 0, 1, 0.5);
        context.FillRect(rect);

        context.RestoreGState();
    }
    public override void Resized(int width, int height)
    {
        _width = width;
        _height = height;
    }
}

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Library.Init();

        var options = new WindowOptions
        {
            MinWidth = 320,
            MinHeight = 200
        };
        var handler = new WindowHandler();
        var window = CreateWindow(800, 600, "this is the first window! 🚀", handler, options);
        handler.Window = window;

        var fileMenu = CreateMenu();
        var exitAction =
            CreateAction("E&xit", null, CreateAccelerator(Key.Q, Modifiers.Control), () =>
            {
                Console.WriteLine("you chose 'exit'!");
                ExitRunloop();
            });
        fileMenu.AddAction(exitAction);

        var menuBar = CreateMenuBar();
        menuBar.AddMenu("&File", fileMenu);
        
        window.SetMenuBar(menuBar);
        
        window.Show();
        Runloop();

        Library.Shutdown();
    }
}
