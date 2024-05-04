using Org.Prefixed.GuiBase;

namespace AppRunner;

public class BaseWindowDelegate : Windowing.WindowDelegate
{
    public virtual bool CanClose() => true;

    public virtual void Closed()
    {
    }

    public virtual void Destroyed()
    {
    }

    public virtual void MouseDown(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }

    public virtual void MouseUp(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }

    public virtual void MouseMove(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public virtual void MouseEnter(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public virtual void MouseLeave(Windowing.Modifiers modifiers)
    {
    }

    public virtual void Repaint(Drawing.DrawContext context, int x, int y, int width, int height)
    {
    }

    public virtual void Moved(int x, int y)
    {
    }

    public virtual void Resized(int width, int height)
    {
    }

    public virtual void KeyDown(Keys.Key key, Windowing.Modifiers modifiers, Keys.KeyLocation location)
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
}
