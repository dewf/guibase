using Org.Prefixed.GuiBase;

namespace AppRunner;

public interface IWindowMethods
{
    void Invalidate(int x, int y, int width, int height);
    void DestroyWindow();
    Windowing.Window GetWindowHandle();
}

public readonly struct RenderArea(int x, int y, int width, int height)
{
    public int X { get; } = x;
    public int Y { get; } = y;
    public int Width { get; } = width;
    public int Height { get; } = height;
}

public interface IPage
{
    bool IsAnimating { get; }
    string PageTitle { get; }
    bool CanDrop { get; }
    Windowing.MenuBar? MenuBar { get; }
    void Render(Drawing.DrawContext context, RenderArea area);
    void Render2(Drawing.DrawContext context, RenderArea area);
    void OnHostWindowMoved();
    void OnSize(int newWidth, int newHeight);
    void OnTimer(double secondsSinceLast);
    void OnMouseMove(int x, int y, Windowing.Modifiers modifiers);
    void OnMouseLeave(Windowing.Modifiers modifiers);
    void OnMouseEnter(int x, int y, Windowing.Modifiers modifiers);
    void OnMouseDown(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers);
    void OnMouseUp(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers);
    void OnKeyDown(Windowing.Key key, Windowing.Modifiers modifiers);
    
    Windowing.DropEffect DropFeedback(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect suggested);
    void DropLeave();
    void DropSubmit(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect effect);

    void DragRender(Windowing.DragRenderPayload payload, string requestedFormat);
}

public abstract class BasePage(IWindowMethods windowMethods) : IPage
{
    protected int Width, Height;
    
    public virtual string PageTitle => "(untitled)";
    public virtual bool IsAnimating => false;
    public virtual bool CanDrop => false;
    public virtual Windowing.MenuBar? MenuBar => null;

    protected void DestroyWindow()
    {
        windowMethods.DestroyWindow();
    }

    protected void Invalidate()
    {
        windowMethods.Invalidate(0, 0, 0, 0);
    }
    
    protected void Invalidate(int x, int y, int width, int height)
    {
        windowMethods.Invalidate(x, y, width, height);
    }
    
    public virtual void OnMouseMove(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public virtual void OnMouseLeave(Windowing.Modifiers modifiers)
    {
    }

    public virtual void OnMouseEnter(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public virtual void OnMouseDown(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }

    public virtual void OnKeyDown(Windowing.Key key, Windowing.Modifiers modifiers)
    {
    }

    public virtual void OnMouseUp(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }
    
    public abstract void Render(Drawing.DrawContext context, RenderArea area);

    public virtual void Render2(Drawing.DrawContext context, RenderArea area)
    {
        Render(context, area);
    }

    public virtual void OnHostWindowMoved()
    {
        // useful for re-showing menus or hiding them or whatever
    }

    public virtual void OnSize(int newWidth, int newHeight)
    {
        Width = newWidth;
        Height = newHeight;
    }

    public virtual void OnTimer(double secondsSinceLast)
    {
    }

    public virtual Windowing.DropEffect DropFeedback(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect suggested)
    {
        return Windowing.DropEffect.None;
    }

    public virtual void DropLeave()
    {
    }

    public virtual void DropSubmit(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect effect)
    {
    }

    public virtual void DragRender(Windowing.DragRenderPayload payload, string requestedFormat)
    {
        throw new NotImplementedException("base page DragRender, you don't want to see this");
    }
}
