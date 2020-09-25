using lab2.ShopSystem.Interface;
using lab2.ShopSystem.Utils;

namespace lab2.ShopSystem.Types
{
    public class Product:IProduct
    {
        public uint Id { get; }
        public string Name { get; }

        private static IdGenerator IG = 
            new IdGenerator();

        public Product(string name)
        {
            /*Id = (uint)this.GetHashCode();*/
            Id = IG.GenerateUniqId();
            Name = name;
        }
    }
}