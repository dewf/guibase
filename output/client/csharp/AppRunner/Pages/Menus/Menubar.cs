using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages.Menus;

public class Menubar
{
    public const int MenuHeight = 32;

    private readonly string[] _menuNames = ["File", "Edit", "View", "Misc", "Help"];
    private readonly Gradient _bgGradient = GetGradient(0.8, 0.8, 0.8, 1, 0.5, 0.5, 0.5, 1);

    public event EventHandler? NeedsInvalidation;

    private struct MenuItem
    {
        public Line Line { get; set; }
        public Rect Bounds { get; set; }
        public Point Position { get; set; }
    }

    private readonly MenuItem[] _items;
    private int _hoverIndex = -1;

    public Menubar()
    {
        using var black = Color.CreateGenericRGB(0, 0, 0, 1);
        using var font = Font.CreateWithName(Constants.HelveticaFontName, 16, new OptArgs());
        
        var x = 10.0;
        _items = _menuNames.Select(menuName =>
        {
            using var attrString = AttributedString.Create(menuName,
                new AttributedStringOptions { Font = font, ForegroundColor = black });
            var line = Line.CreateWithAttributedString(attrString);

            var tBounds = line.GetTypographicBounds();
            var bounds = line.GetBoundsWithOptions(0);
            var y = (MenuHeight - bounds.Size.Height) / 2;

            bounds.Origin.X = x - 5;
            bounds.Size.Width += 10;
            bounds.Origin.Y = y;
            var textPosition = new Point(x, y + tBounds.Ascent);

            var item = new MenuItem { Line = line, Bounds = bounds, Position = textPosition };
            x += bounds.Size.Width + 8;

            return item;
        }).ToArray();
    }

    public void OnMouseMove(int x, int y)
    {
        var p = new Point(x, y);
        var lastIndex = _hoverIndex;
        _hoverIndex = Array.FindIndex(_items, item => item.Bounds.ContainsPoint(p));
        if (_hoverIndex != lastIndex)
        {
            // repaint necessary
            var invalidation = NeedsInvalidation;
            invalidation?.Invoke(this, EventArgs.Empty);
        }
    }
    
    public void Render(DrawContext context, int width)
    {
        context.SaveGState();

        // var rect = MakeRect(0, 0, width, MenuHeight);
        context.DrawLinearGradient(_bgGradient, new Point(0, 0), new Point(0, MenuHeight), 0);

        var i = 0;
        foreach (var item in _items)
        {
            context.SetTextPosition(item.Position.X, item.Position.Y);
            if (i == _hoverIndex)
            {
                context.SetRGBFillColor(0, 0.8, 1, 0.25);
                var highlightRect = MakeRect(item.Bounds.Origin.X, 0, item.Bounds.Size.Width, MenuHeight);
                using var rectPath = Drawing.Path.CreateWithRoundedRect(highlightRect, 5, 5, new OptArgs());
                context.AddPath(rectPath);
                context.FillPath();
            }
            item.Line.Draw(context);
            i++;
        }
        
        context.RestoreGState();
    }
}