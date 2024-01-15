using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

namespace Org.Prefixed.GuiBase
{
    public static class Drawing
    {
        private static ModuleHandle _module;
        private static InterfaceHandle _drawContext;
        private static InterfaceMethodHandle _drawContext_saveGState;
        private static InterfaceMethodHandle _drawContext_restoreGState;
        private static InterfaceMethodHandle _drawContext_setRGBFillColor;
        private static InterfaceMethodHandle _drawContext_fillRect;

        public struct Point {
            public double X;
            public double Y;
            public Point(double x, double y)
            {
                this.X = x;
                this.Y = y;
            }
        }

        internal static void Point__Push(Point value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Y);
            NativeImplClient.PushDouble(value.X);
        }

        internal static Point Point__Pop()
        {
            var x = NativeImplClient.PopDouble();
            var y = NativeImplClient.PopDouble();
            return new Point(x, y);
        }

        public struct Size {
            public double Width;
            public double Height;
            public Size(double width, double height)
            {
                this.Width = width;
                this.Height = height;
            }
        }

        internal static void Size__Push(Size value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Height);
            NativeImplClient.PushDouble(value.Width);
        }

        internal static Size Size__Pop()
        {
            var width = NativeImplClient.PopDouble();
            var height = NativeImplClient.PopDouble();
            return new Size(width, height);
        }

        public struct Rect {
            public Point Origin;
            public Size Size;
            public Rect(Point origin, Size size)
            {
                this.Origin = origin;
                this.Size = size;
            }
        }

        internal static void Rect__Push(Rect value, bool isReturn)
        {
            Size__Push(value.Size, isReturn);
            Point__Push(value.Origin, isReturn);
        }

        internal static Rect Rect__Pop()
        {
            var origin = Point__Pop();
            var size = Size__Pop();
            return new Rect(origin, size);
        }


        public interface DrawContext : IDisposable
        {
            void SaveGState();
            void RestoreGState();
            void SetRGBFillColor(double red, double green, double blue, double alpha);
            void FillRect(Rect rect);
        }

        internal static void DrawContext__Push(DrawContext thing, bool isReturn)
        {
            if (thing != null)
            {
                ((IPushable)thing).Push(isReturn);
            }
            else
            {
                NativeImplClient.PushNull();
            }
        }

        internal static DrawContext DrawContext__Pop()
        {
            NativeImplClient.PopInstanceId(out var id, out var isClientId);
            if (id != 0)
            {
                if (!isClientId)
                {
                    return new ServerDrawContext(id);
                }
                else
                {
                    return (DrawContext) ClientObject.GetById(id);
                }
            }
            else
            {
                return null;
            }
        }

        public abstract class ClientDrawContext : ClientObject, DrawContext
        {
            public virtual void Dispose()
            {
                // override if necessary
            }
            public abstract void SaveGState();
            public abstract void RestoreGState();
            public abstract void SetRGBFillColor(double red, double green, double blue, double alpha);
            public abstract void FillRect(Rect rect);
        }

        internal class ServerDrawContext : ServerObject, DrawContext
        {
            public ServerDrawContext(int id) : base(id)
            {
            }

            public void SaveGState()
            {
                NativeImplClient.InvokeInterfaceMethod(_drawContext_saveGState, Id);
            }

            public void RestoreGState()
            {
                NativeImplClient.InvokeInterfaceMethod(_drawContext_restoreGState, Id);
            }

            public void SetRGBFillColor(double red, double green, double blue, double alpha)
            {
                NativeImplClient.PushDouble(alpha);
                NativeImplClient.PushDouble(blue);
                NativeImplClient.PushDouble(green);
                NativeImplClient.PushDouble(red);
                NativeImplClient.InvokeInterfaceMethod(_drawContext_setRGBFillColor, Id);
            }

            public void FillRect(Rect rect)
            {
                Rect__Push(rect, false);
                NativeImplClient.InvokeInterfaceMethod(_drawContext_fillRect, Id);
            }

            public void Dispose()
            {
                ServerDispose();
            }
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Drawing");

            _drawContext = NativeImplClient.GetInterface(_module, "DrawContext");
            _drawContext_saveGState = NativeImplClient.GetInterfaceMethod(_drawContext, "saveGState");
            _drawContext_restoreGState = NativeImplClient.GetInterfaceMethod(_drawContext, "restoreGState");
            _drawContext_setRGBFillColor = NativeImplClient.GetInterfaceMethod(_drawContext, "setRGBFillColor");
            _drawContext_fillRect = NativeImplClient.GetInterfaceMethod(_drawContext, "fillRect");

            NativeImplClient.SetClientMethodWrapper(_drawContext_saveGState, delegate(ClientObject obj)
            {
                var inst = (ClientDrawContext) obj;
                inst.SaveGState();
            });

            NativeImplClient.SetClientMethodWrapper(_drawContext_restoreGState, delegate(ClientObject obj)
            {
                var inst = (ClientDrawContext) obj;
                inst.RestoreGState();
            });

            NativeImplClient.SetClientMethodWrapper(_drawContext_setRGBFillColor, delegate(ClientObject obj)
            {
                var inst = (ClientDrawContext) obj;
                var red = NativeImplClient.PopDouble();
                var green = NativeImplClient.PopDouble();
                var blue = NativeImplClient.PopDouble();
                var alpha = NativeImplClient.PopDouble();
                inst.SetRGBFillColor(red, green, blue, alpha);
            });

            NativeImplClient.SetClientMethodWrapper(_drawContext_fillRect, delegate(ClientObject obj)
            {
                var inst = (ClientDrawContext) obj;
                var rect = Rect__Pop();
                inst.FillRect(rect);
            });

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
