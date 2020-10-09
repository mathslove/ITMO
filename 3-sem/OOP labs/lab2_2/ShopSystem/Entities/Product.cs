using lab2_pro.ShopSystem.Interface;

namespace lab2_pro.ShopSystem.Entities
{
    public class Product: IProduct
    {
        protected uint Id;
        protected string Name;

        public Product(string name)
        {
            Id = (uint)GetHashCode();
            Name = name;
        }
        
        public Product(uint id, string name)
        {
            Id = id;
            Name = name;
        }

        public Product(Product prod)
        {
            Id = prod.Id;
            Name = prod.Name;
        }

        public uint GetId()
        {
            return Id;
        }
        
        public string GetName()
        {
            return Name;
        }
    }
}