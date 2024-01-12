namespace AppRunner;

using static Org.Prefixed.GuiBase.Windowing;

internal class WindowHandler : ClientIWindowDelegate
{
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
    public override void MouseDown(int x, int y, MouseButton button, HashSet<Modifiers> modifiers)
    {
        Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
    }
    private static string ModifiersToString(HashSet<Modifiers> modifiers)
    {
        return string.Join("+", modifiers.Select(m => m.ToString()).Order());
    }
}

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Init();
        var props = new WindowProperties
        {
            UsedFields = PropFlags.MinWidth | PropFlags.MaxWidth | PropFlags.MinHeight | PropFlags.MaxHeight | PropFlags.Style,
            MinWidth = 320,
            MinHeight = 200,
            MaxWidth = 1280,
            MaxHeight = 960,
            Style = WindowStyle.Default
        };
        using (var window = CreateWindow(800, 600, "this is the first window!", new WindowHandler(), props))
        {
            window.Show();
            Runloop();
            Console.WriteLine("last line of 'using'");
        }
        Console.WriteLine("before shutdown");
        Shutdown();
    }
}
