﻿namespace Org.Prefixed.GuiBase.Support
{
    public abstract class ClientObject : ClientResource
    {
        protected override void NativePush()
        {
            NativeMethods.pushInstance(Id, true);
        }
        public static ClientObject GetById(int id)
        {
            return (ClientObject)GetResourceById(id);
        }
    }
}
