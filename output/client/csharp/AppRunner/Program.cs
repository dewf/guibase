using System.Diagnostics;
using AppRunner.Pages;
using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;

namespace AppRunner;

internal class MainWindowDelegate : ClientWindowDelegate, IWindowMethods
{
    private int _width, _height;
    private readonly MenuBar _emptyMenuBar = MenuBar.Create();

    private Window? _window;
    public Window? Window
    {
        get => _window;
        set
        {
            _window = value;
            _window!.SetTitle(_currentPage.PageTitle);
            _window!.EnableDrops(_currentPage.CanDrop);
        }
    }

    private readonly SpinningFlower _page01;
    private readonly TextBoundsCircle _page02;
    private readonly TextStrokeFill _page03;
    private readonly ResizeGradient _page04;
    private readonly TextFormattingPage _page05;
    private readonly GradLabelPage _page06;
    private readonly TextStrokeTestingPage _page07;
    private readonly TextSelectionPage _page08;
    private readonly TransformedShapesPage _page09;
    private readonly WindowEventStuff _page10;
    private IPage _currentPage;

    private readonly Stopwatch _watch = new();

    public bool IsDestroyed { get; private set; }

    public MainWindowDelegate()
    {
        // page init
        _page01 = new SpinningFlower(this);
        _page02 = new TextBoundsCircle(this);
        _page03 = new TextStrokeFill(this);
        _page04 = new ResizeGradient(this);
        _page05 = new TextFormattingPage(this);
        _page06 = new GradLabelPage(this);
        _page07 = new TextStrokeTestingPage(this);
        _page08 = new TextSelectionPage(this);
        _page09 = new TransformedShapesPage(this);
        _page10 = new WindowEventStuff(this);
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
        _currentPage.OnMouseDown(x, y, button, modifiers);
    }

    public override void MouseUp(int x, int y, MouseButton button, Modifiers modifiers)
    {
        _currentPage.OnMouseUp(x, y, button, modifiers);
    }

    public override void MouseMove(int x, int y, Modifiers modifiers)
    {
        _currentPage.OnMouseMove(x, y, modifiers);
    }

    public override void MouseLeave(Modifiers modifiers)
    {
        _currentPage.OnMouseLeave(modifiers);
    }

    public override void MouseEnter(int x, int y, Modifiers modifiers)
    {
        _currentPage.OnMouseEnter(x, y, modifiers);
    }
    
    private void SelectPage(IPage page)
    {
        _currentPage = page;
        _currentPage.OnSize(_width, _height);
        Window!.SetTitle(_currentPage.PageTitle);
        Window!.EnableDrops(_currentPage.CanDrop);
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
            case Key._4:
                SelectPage(_page04);
                break;
            case Key._5:
                SelectPage(_page05);
                break;
            case Key._6:
                SelectPage(_page06);
                break;
            case Key._7:
                SelectPage(_page07);
                break;
            case Key._8:
                SelectPage(_page08);
                break;
            case Key._9:
                SelectPage(_page09);
                break;
            case Key._0:
                SelectPage(_page10);
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
        // _watch.Restart();
        
        // don't think we need to save/restore state, created afresh every time?
        // will have to see how macOS behaves ...
        context.SaveGState();
        _currentPage.Render(context, new RenderArea(x, y, width, height));
        context.RestoreGState();
        
        // _watch.Stop();
        // Console.WriteLine($"rendering time: {_watch.ElapsedMilliseconds}ms");
    }
    public override void Resized(int width, int height)
    {
        _width = width;
        _height = height;
        _currentPage.OnSize(_width, _height);
    }

    public override DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested)
    {
        return _currentPage.CanDrop ? _currentPage.DropFeedback(data, x, y, modifiers, suggested) : DropEffect.None;
    }

    public override void DropLeave()
    {
        if (_currentPage.CanDrop) _currentPage.DropLeave();
    }

    public override void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect)
    {
        if (_currentPage.CanDrop) _currentPage.DropSubmit(data, x, y, modifiers, effect);
    }

    public void Invalidate(int x, int y, int width, int height)
    {
        Window!.Invalidate(x, y, width, height);
    }

    public void TimerTick(double secondsSinceLast)
    {
        if (_currentPage.IsAnimating)
        {
            _currentPage.OnTimer(secondsSinceLast);
        }
    }
    
    public void DestroyWindow()
    {
        Window!.Destroy();
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
