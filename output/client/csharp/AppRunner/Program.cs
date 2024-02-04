using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Windowing;

namespace AppRunner;

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Library.Init();

        // scope for opaque disposal, prior to library exit
        {
            var window = MainWindow.Create();

            using var timer = Windowing.Timer.Create(1000 / 60, secondsSinceLast =>
            {
                if (!window.IsDestroyed)
                {
                    window.TimerTick(secondsSinceLast);
                }
            });
        
            window.Show();
            Runloop();
            
            // disposal of everything 'using' upon leaving this scope!
        }
        
        Library.Shutdown();
    }
}
