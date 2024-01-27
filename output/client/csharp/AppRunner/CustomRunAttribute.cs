using Org.Prefixed.GuiBase;

namespace AppRunner;

internal abstract class CustomRunAttribute
{
    public virtual Drawing.Color GetColor()
    {
        throw new Exception("CustomRunAttribute - wrong type!");
    }
    public virtual int GetInt()
    {
        throw new Exception("CustomRunAttribute - wrong type!");
    }
    public virtual UnderlineStyle GetUnderlineStyle()
    {
        throw new Exception("CustomRunAttribute - wrong type!");
    }
}
internal class ColorAttribute(Drawing.Color color) : CustomRunAttribute
{
    public override Drawing.Color GetColor() => color;
}
internal class IntAttribute(int value) : CustomRunAttribute
{
    public override int GetInt() => value;
}

internal enum UnderlineStyle
{
    Single,
    Double,
    Triple,
    Squiggly,
    Overline
}
internal class UnderlineStyleAttribute(UnderlineStyle style) : CustomRunAttribute
{
    public override UnderlineStyle GetUnderlineStyle() => style;
}
