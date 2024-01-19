using Org.Prefixed.GuiBase;

namespace AppRunner;

internal class WindowHandler : Windowing.ClientWindowDelegate
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
        Windowing.ExitRunloop();
    }
    public override void MouseDown(int x, int y, Windowing.MouseButton button, HashSet<Windowing.Modifiers> modifiers)
    {
        Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
    }
    private static string ModifiersToString(HashSet<Windowing.Modifiers> modifiers)
    {
        return string.Join("+", modifiers.Select(m => m.ToString()).Order());
    }
    public override void Repaint(Drawing.DrawContext context, int x, int y, int width, int height)
    {
        context.SaveGState();
        
        // bordered
        context.SetRGBFillColor(0.23, 0, 0.4, 1);
        context.FillRect(new Drawing.Rect(new Drawing.Point(10, 10), new Drawing.Size(_width - 20, _height - 20)));

        // overlapping
        var rect = new Drawing.Rect(new Drawing.Point(100, 100), new Drawing.Size(100, 100));
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

        var options = new Windowing.WindowOptions
        {
            MinWidth = 320,
            MinHeight = 200
        };
        var window = Windowing.CreateWindow(800, 600, "this is the first window! 🚀", new WindowHandler(), options);
        window.Show();
        Windowing.Runloop();

        Library.Shutdown();
    }
}
