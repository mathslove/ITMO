namespace lab2_2.ShopSystem.Types
{
    public class Product
    {

        
        public int Id;
        public string Name;

        public Product(string name)
        {
            Id = this.GetHashCode();
            Name = name;
        }
    }
}