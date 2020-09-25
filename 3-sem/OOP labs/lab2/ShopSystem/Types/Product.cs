using lab2.ShopSystem.Interface;
using lab2.ShopSystem.Utils;

namespace lab2.ShopSystem.Types
{
    public class Product:IProduct
    {
        public uint Id { get; }
        public string Name { get; }

        public Product(uint id, string name)
        {
            Id = id;
            Name = name;
        }
    }
}