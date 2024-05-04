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
        Drawing.__Init();
        Text.__Init();
        Keys.__Init();
        Windowing.__Init();
    }

    public static void Shutdown()
    {
        // module static shutdowns (if any, might be empty)
        Windowing.__Shutdown();
        Keys.__Shutdown();
        Text.__Shutdown();
        Drawing.__Shutdown();
        // bye
        NativeImplClient.Shutdown();
    }

    public static void DumpTables()
    {
        NativeImplClient.DumpTables();
    }
}
