namespace lab2.ShopSystem.Interface
{
    public interface IProduct: IEntity
    {
        public uint Id { get;  }
        public string Name { get; }
    }
}