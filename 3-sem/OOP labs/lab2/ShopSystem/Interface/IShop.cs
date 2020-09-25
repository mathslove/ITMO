namespace lab2.ShopSystem.Interface
{
    public interface IShop:IEntity
    {
        public string Address { get;  }
        public uint Id { get; }
        public string Name { get; }
    }
}