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
    private readonly Page02 _page02;
    private readonly Page03 _page03;
    private IPage _currentPage;

    public bool IsDestroyed { get; private set; }

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
        _page02 = new Page02(this);
        _page02.Init();
        _page03 = new Page03(this);
        _page03.Init();

        _currentPage = _page01;
    }

    public override bool CanClose() => true;

    public override void Closed()
    {
        Console.WriteLine("window closed!!");
    }

    public override void Destroyed()
    {
        IsDestroyed = true;
        Console.WriteLine("window destroyed! exiting runloop");
        ExitRunloop();
    }

    public override void MouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        // Console.WriteLine($"button press @ {x}/{y}/{button}/{ModifiersToString(modifiers)}");
        if (button == MouseButton.Right)
        {
            Window!.ShowContextMenu(x, y, _contextMenu);
        }
        else
        {
            _currentPage.OnMouseDown(x, y, button, modifiers);
        }
    }
    
    public override void MouseMove(int x, int y, Modifiers modifiers)
    {
        _currentPage.OnMouseMove(x, y, modifiers);
    }

    private void SelectPage(IPage page)
    {
        _currentPage = page;
        _currentPage.OnSize(_width, _height);
        Invalidate(0, 0, _width, _height);
    }

    public override void KeyDown(Key key, Modifiers modifiers, KeyLocation location)
    {
        switch (key)
        {
            case Key._1:
                SelectPage(_page01);
                break;
            case Key._2:
                SelectPage(_page02);
                break;
            case Key._3:
                SelectPage(_page03);
                break;
            default:
                _currentPage.OnKeyDown(key, modifiers);
                break;
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
        // don't think we need to save/restore state, created afresh every time?
        // will have to see how macOS behaves ...
        context.SaveGState();
        _currentPage.Render(context, new RenderArea(x, y, width, height));
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

    public void TimerTick(double secondsSinceLast)
    {
        _currentPage.OnTimer(secondsSinceLast);
    }
}

internal static class Program
{
    [STAThread]
    private static void Main(string[] args)
    {
        Library.Init();

        // scope for opaque disposal, prior to library exit
        {
            var options = new WindowOptions
            {
                MinWidth = Constants.MinWidth,
                MinHeight = Constants.MinHeight,
                MaxWidth = Constants.MaxWidth,
                MaxHeight = Constants.MaxHeight
            };
            var mainWinDel = new MainWindowDelegate();
            using var window = Window.Create(Constants.InitWidth, Constants.InitHeight, "this is the first window! 🚀", mainWinDel, options);
            mainWinDel.Window = window;

            using var fileMenu = Menu.Create();
            using var exitAction =
                Windowing.Action.Create("E&xit", null, Accelerator.Create(Key.Q, Modifiers.Control), () =>
                {
                    Console.WriteLine("you chose 'exit'!");
                    ExitRunloop();
                });
            fileMenu.AddAction(exitAction);

            using var menuBar = MenuBar.Create();
            menuBar.AddMenu("&File", fileMenu);
        
            window.SetMenuBar(menuBar);

            using var timer = Windowing.Timer.Create(1000 / 60, secondsSinceLast =>
            {
                if (!mainWinDel.IsDestroyed)
                {
                    mainWinDel.TimerTick(secondsSinceLast);
                }
            });
        
            window.Show();
            Runloop();
            
            // disposal of everything upon leaving this scope!
        }
        Library.Shutdown();
    }
}
