using System.Diagnostics;
using Org.Prefixed.GuiBase.Support;

namespace Org.Prefixed.GuiBase;

public static class Library
{
    public static void Init()
    {
        Debug.Assert(NativeImplClient.Init() == 0);
        // registrations, static module inits
        Drawing.Init();
        Windowing.Init();
    }

    public static void Shutdown()
    {
        // module static shutdowns (if any, might be empty)
        Windowing.Shutdown();
        Drawing.Shutdown();
        // bye
        NativeImplClient.Shutdown();
    }

    public static void DumpTables()
    {
        NativeImplClient.DumpTables();
    }
}
