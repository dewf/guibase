using Org.Prefixed.GuiBase;
using static AppRunner.Common;
using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public class GradLabelPage(IWindowMethods windowMethods) : BasePage(windowMethods)
{
	private const string Text = "Vestibulum mattis ipsum augue, ac maximus erat scelerisque vitae. Nam vel commodo urna, a consectetur arcu. Quisque a suscipit metus. Nam bibendum accumsan vulputate. Proin suscipit, sapien a fermentum laoreet, est turpis sollicitudin ipsum, quis consectetur purus augue non ante. Donec sollicitudin erat sed urna posuere vehicula. Sed lacus felis, dapibus sed leo vel, pretium gravida lectus. Fusce id eros euismod, cursus ante sit amet, tempus tortor. Aenean venenatis quam ut tortor aliquet ornare. Curabitur sollicitudin molestie nisi, sit amet sollicitudin tortor maximus at. Phasellus eget vehicula ligula. Ut eu tempus urna. Donec tempor velit in odio vulputate, id condimentum justo finibus. Donec cursus nulla et pellentesque finibus. Phasellus tincidunt ligula pellentesque pulvinar ultrices. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed malesuada mauris ac tortor consequat gravida et non urna. Interdum et malesuada fames ac ante ipsum primis in faucibus. Proin vitae justo erat. Suspendisse potenti. Sed sit amet leo in sapien placerat maximus vitae eget tellus. Etiam ullamcorper augue eros, at mollis libero placerat id. Nulla id suscipit quam, non rhoncus tellus. Nulla mauris elit, congue id accumsan in, pellentesque ullamcorper nisi. In a elit mi. Quisque feugiat justo at ipsum lacinia finibus.";
	private const string BigLabelText = "BIG-LABEL";
	private const string GradLabelText = "GRAD-LABEL";
	private static void DrawTextInShape(DrawContext context, Drawing.Path path, string text, Color color, Font font, TextAlignment? alignment = null)
	{
		using var attrString = MutableAttributedString.Create(0); // 0 = amt of storage to reserve, no hint
		attrString.ReplaceString(RangeZero, text);
		var fullRange = MakeRange(0, attrString.GetLength());
		
		attrString.SetAttribute(fullRange, new AttributedStringOptions { ForegroundColor = color });
		attrString.SetAttribute(fullRange, new AttributedStringOptions { Font = font });
		if (alignment != null)
		{
			using var pStyle = ParagraphStyle.Create([new ParagraphStyleSetting.Alignment(alignment.Value)]);
			attrString.SetAttribute(fullRange, new AttributedStringOptions { ParagraphStyle = pStyle });
		}
		
		// framesetter
		using var frameSetter = FrameSetter.CreateWithAttributedString(attrString);
		using var frame = frameSetter.CreateFrame(RangeZero, path);
		
		// draw
		frame.Draw(context);
	}

	private void DoBigLabel(DrawContext context)
	{
		var helv120 = Font.CreateWithName("Arial", 120, new OptArgs());

		using var strokeColor = Color.CreateGenericRGB(1, 1, 0, 1);
		using var fgColor = Color.CreateGenericRGB(0, 0, 0, 1);
		using var labelString = AttributedString.Create(BigLabelText, new AttributedStringOptions
		{
			Font = helv120,
			StrokeWidth = -2,
			StrokeColor = strokeColor,
			ForegroundColor = fgColor
		});

		using var line = Line.CreateWithAttributedString(labelString);

		var bounds = line.GetBoundsWithOptions(0);
		var typoBounds = line.GetTypographicBounds();
		
		context.SetTextPosition((Width - bounds.Size.Width) / 2, 10 + typoBounds.Ascent);

		line.Draw(context);
	}

	private void DoGradientLabel(DrawContext context)
	{
		using var helv180 = Font.CreateWithName("Arial", 180, new OptArgs());
		using var labelString = AttributedString.Create(GradLabelText, new AttributedStringOptions { Font = helv180 });

		using var line = Line.CreateWithAttributedString(labelString);
		var bounds = line.GetBoundsWithOptions(LineBoundsOptions.UseGlyphPathBounds);
		var typoBounds = line.GetTypographicBounds();
		var x = (Width - bounds.Size.Width) / 2;
		var y = Height - (typoBounds.Leading + 10);

		context.SetTextPosition(x, y);

		// begin clip ====>
		context.SaveGState();
		context.SetTextDrawingMode(TextDrawingMode.Clip);
		line.Draw(context);
		
		// now do gradient inside of clip
		using var grad = GetGradient(0, 0, 0, 1, 0, 1, 1, 1);
		var start = new Point(x, y + bounds.Origin.Y); // top left of bounds rect (y is negative, relative to baseline)
		var end = new Point(x, y + bounds.Origin.Y + bounds.Size.Height); // bottom left of bounds rect
		context.DrawLinearGradient(grad, start, end, GradientDrawingOptions.DrawsBeforeStartLocation | GradientDrawingOptions.DrawsAfterEndLocation);
		
		context.RestoreGState();
		// <==== end clip

		// create image to use for masking
		using var graySpace = ColorSpace.CreateDeviceGray();
		using var bitmapContext =
			BitmapDrawContext.Create(Width, Height, 8, Width, graySpace, BitmapInfo.ByteOrderDefault);
		using var black = Color.GetConstantColor(ColorConstants.Black); // "using" but it should survive release, constant colors are eternal
		bitmapContext.SetFillColorWithColor(black);
		bitmapContext.FillRect(MakeRect(0, 0, Width, Height));

		// draw outside stroke on mask
		bitmapContext.SetTextPosition(x, y);
		bitmapContext.SetTextDrawingMode(TextDrawingMode.Stroke);
		using var white = Color.GetConstantColor(ColorConstants.White);
		bitmapContext.SetStrokeColorWithColor(white);
		bitmapContext.SetLineWidth(4);
		line.Draw(bitmapContext);

		// apply bitmap as mask ===>
		context.SaveGState();

		using var image = bitmapContext.CreateImage();
		context.ClipToMask(MakeRect(0, 0, Width, Height), image);

		// fill 2nd gradient over masked outline
		using var grad2 = GetGradient(1, 0.5, 0, 1, 0, 0, 0, 1);
		context.DrawLinearGradient(grad2, start, end, GradientDrawingOptions.DrawsBeforeStartLocation | GradientDrawingOptions.DrawsAfterEndLocation);
		
		context.RestoreGState();
		// <=== end mask
	}
	
    public override void Render(DrawContext context, RenderArea area)
    {
        // gradient for fun
        using var grad = GetGradient(0, 0.5, 1, 1, 0, 0, 0, 1);
        context.DrawLinearGradient(grad, new Drawing.Point(0, Height), PointZero, 0);
        
		context.SetTextMatrix(AffineTransformIdentity);

		// colors
		using var white = Color.CreateGenericRGB(1, 1, 1, 1);
		using var black = Color.CreateGenericRGB(0, 0, 0, 1);
		using var green = Color.CreateGenericRGB(0, 1, 0, 1);
		using var yellow = Color.CreateGenericRGB(1, 1, 0, 1);

		// font
		using var times40 = Font.CreateWithName("Times New Roman", 40, new OptArgs());
		using var helv16 = Font.CreateWithName("Arial", 16, new OptArgs());
		using var futura32 = Font.CreateWithName("Impact", 32, new OptArgs());
		
		// shapes
		var totalRect = Drawing.Path.CreateWithRect(MakeRect(0, 0, Width, Height).Inset(10), new OptArgs()); // whole window minus borders
		var rightRect = Drawing.Path.CreateWithRect(MakeRect(Width - 400, 0, 400, Height).Inset(10), new OptArgs()); // right side, top to bottom
		var midLeftRect = Drawing.Path.CreateWithRect(MakeRect(50, (Height - 300.0) / 2, 300, 300), new OptArgs()); // mid-left-side, 300px wide/tall
		
		// text drawing
		DrawTextInShape(context, totalRect, Text, black, times40);

		context.SetRGBStrokeColor(1, 0, 0, 1);
		context.AddPath(midLeftRect);
		context.StrokePath();
		
		DrawTextInShape(context, midLeftRect, Text, white, helv16, TextAlignment.Justified);
		DrawTextInShape(context, rightRect, Text, green, futura32, TextAlignment.Right);
		
		DoBigLabel(context);
		
		DoGradientLabel(context);
    }
}
