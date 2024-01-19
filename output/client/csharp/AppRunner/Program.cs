using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;

namespace AppRunner;

internal class WindowHandler : ClientWindowDelegate
{
    private int _width, _height;
    
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

    public override void MouseDown(int x, int y, MouseButton button, HashSet<Modifier> modifiers)
    {
        Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
    }
    private static string ModifiersToString(HashSet<Modifier> modifiers)
    {
        return string.Join("+", modifiers.Select(m => m.ToString()).Order());
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

    public override void PerformAction(int id, Windowing.Action action)
    {
        if (id == 101)
        {
            Console.WriteLine("Exiting!");
            ExitRunloop();
        }
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
        var window = CreateWindow(800, 600, "this is the first window! 🚀", new WindowHandler(), options);

        var fileMenu = CreateMenu();
        var quitMods = new HashSet<Modifier>(new[] { Modifier.Control });
        var exitAction =
            CreateAction(101, "E&xit", null, CreateAccelerator(Key.Q, quitMods));
        fileMenu.AddAction(exitAction);

        var menuBar = CreateMenuBar();
        menuBar.AddMenu("&File", fileMenu);
        
        window.SetMenuBar(menuBar);
        
        window.Show();
        Runloop();

        Library.Shutdown();
    }
}
