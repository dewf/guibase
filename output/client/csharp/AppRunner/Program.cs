namespace AppRunner;

using Org.Prefixed.GuiBase;

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
}

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Windowing.Init();
        using (var window = Windowing.CreateWindow(800, 600, "this is the first window!", new WindowHandler()))
        {
            window.Show();
            Windowing.Runloop();
            Console.WriteLine("last line of 'using'");
        }
        Console.WriteLine("before shutdown");
        Windowing.Shutdown();
    }
}
