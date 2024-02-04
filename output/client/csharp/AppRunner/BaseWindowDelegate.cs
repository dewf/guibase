using Org.Prefixed.GuiBase;

namespace AppRunner;

public class BaseWindowDelegate : Windowing.ClientWindowDelegate
{
    public override bool CanClose() => true;

    public override void Closed()
    {
    }

    public override void Destroyed()
    {
    }

    public override void MouseDown(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }

    public override void MouseUp(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
    }

    public override void MouseMove(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public override void MouseEnter(int x, int y, Windowing.Modifiers modifiers)
    {
    }

    public override void MouseLeave(Windowing.Modifiers modifiers)
    {
    }

    public override void Repaint(Drawing.DrawContext context, int x, int y, int width, int height)
    {
    }

    public override void Moved(int x, int y)
    {
    }

    public override void Resized(int width, int height)
    {
    }

    public override void KeyDown(Windowing.Key key, Windowing.Modifiers modifiers, Windowing.KeyLocation location)
    {
    }

    public override void DragRender(Windowing.DragRenderPayload payload, string requestedFormatMIME)
    {
        throw new NotImplementedException("BaseWindowDelegate.DragRender() - you probably want to do something here");
    }

    public override Windowing.DropEffect DropFeedback(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect suggested)
    {
        return Windowing.DropEffect.None;
    }

    public override void DropLeave()
    {
    }

    public override void DropSubmit(Windowing.DropData data, int x, int y, Windowing.Modifiers modifiers, Windowing.DropEffect effect)
    {
    }
}