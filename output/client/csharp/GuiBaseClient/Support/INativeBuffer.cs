namespace Org.Prefixed.GuiBase.Support
{
    public interface INativeBuffer<T> : IDisposable
    {
        public Span<T> GetSpan(out int length);
    }
}
