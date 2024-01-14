using Org.Prefixed.GuiBase;

namespace AppRunner;

internal class WindowHandler : Windowing.ClientIWindowDelegate
{
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
    public override void Repaint(Drawing.CGContext context, int x, int y, int width, int height)
    {
        // context.SetRGBFillColor(1.0, 1.0, 1.0, 1.0);
        // var rect = new Drawing.Rect(new Drawing.Point(30.0, 10.0), new Drawing.Size(100.0, 100.0));
        // context.FillRect(rect);
        Console.WriteLine($"repaint!!! {x} / {y} / {width} / {height}");
    }
}

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Library.Init();

        var props = new Windowing.WindowProperties
        {
            MinWidth = 320,
            MinHeight = 200,
            MaxWidth = 1280,
            MaxHeight = 960,
            Style = Windowing.WindowStyle.Default
        };
        using (var window = Windowing.CreateWindow(800, 600, "this is the first window!", new WindowHandler(), props))
        {
            window.Show();
            Windowing.Runloop();
            Console.WriteLine("last line of 'using'");
        }
        Console.WriteLine("before shutdown");
        
        Library.Shutdown();
    }
}
