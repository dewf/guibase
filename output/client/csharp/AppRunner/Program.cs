using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;

namespace AppRunner;

internal class MainWindowDelegate : ClientWindowDelegate, IWindowMethods
{
    private int _width, _height;
    private readonly Menu _contextMenu;
    public Window? Window { get; set; }
    private readonly Page01 _page01;
    private IPage _currentPage;
    
    public MainWindowDelegate()
    {
        _contextMenu = Menu.Create();
        _contextMenu.AddAction(Windowing.Action.Create("Context Item", null, null, () =>
        {
            Console.WriteLine("context item clicked!");
        }));

        // page init
        _page01 = new Page01(this);
        _page01.Init();

        _currentPage = _page01;
    }

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

    public override void MouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
        if (button == MouseButton.Right)
        {
            Window!.ShowContextMenu(x, y, _contextMenu);
        }
    }
    private static string ModifiersToString(Modifiers modifiers)
    {
        var strings = 
            from modifier in new[] { Modifiers.Shift, Modifiers.Control, Modifiers.Alt, Modifiers.MacControl } where modifiers.HasFlag(modifier) select modifier.ToString();
        return string.Join("+", strings);
    }
    public override void Repaint(DrawContext context, int x, int y, int width, int height)
    {
        context.SaveGState();
        _currentPage.Render(context, x, y, width, height);
        context.RestoreGState();
    }
    public override void Resized(int width, int height)
    {
        _width = width;
        _height = height;
        _currentPage.OnSize(_width, _height);
    }

    public void Invalidate(int x, int y, int width, int height)
    {
        Window!.Invalidate(x, y, width, height);
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
        var mainWinDel = new MainWindowDelegate();
        var window = Window.Create(800, 600, "this is the first window! 🚀", mainWinDel, options);
        mainWinDel.Window = window;

        var fileMenu = Menu.Create();
        var exitAction =
            Windowing.Action.Create("E&xit", null, Accelerator.Create(Key.Q, Modifiers.Control), () =>
            {
                Console.WriteLine("you chose 'exit'!");
                ExitRunloop();
            });
        fileMenu.AddAction(exitAction);

        var menuBar = MenuBar.Create();
        menuBar.AddMenu("&File", fileMenu);
        
        window.SetMenuBar(menuBar);
        
        window.Show();
        Runloop();

        Library.Shutdown();
    }
}
