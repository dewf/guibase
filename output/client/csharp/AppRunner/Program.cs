namespace AppRunner;

using Org.Prefixed.GuiBase;

internal static class Program
{
    private static void Main(string[] args)
    {
        Windowing.Init();
        Windowing.Shutdown();
    }
}
