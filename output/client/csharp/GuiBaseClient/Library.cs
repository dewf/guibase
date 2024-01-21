using Org.Prefixed.GuiBase.Support;

namespace Org.Prefixed.GuiBase;

public static class Library
{
    public static void Init()
    {
        if (NativeImplClient.Init() != 0)
        {
            Console.WriteLine("NativeImplClient.Init failed");
            return;
        }
        // registrations, static module inits
        Foundation.Init();
        Drawing.Init();
        Windowing.Init();
    }

    public static void Shutdown()
    {
        // module static shutdowns (if any, might be empty)
        Windowing.Shutdown();
        Drawing.Shutdown();
        Foundation.Shutdown();
        // bye
        NativeImplClient.Shutdown();
    }

    public static void DumpTables()
    {
        NativeImplClient.DumpTables();
    }
}
