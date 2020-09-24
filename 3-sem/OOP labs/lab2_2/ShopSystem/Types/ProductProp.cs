using lab2_2.ShopSystem.Exceptions;

namespace lab2_2.ShopSystem.Types
{
    public class ProductProp
    {
        public uint Price { get; set; }

        public uint Amount { get; set; }

        public ProductProp(uint price, uint amount)
        {
            if (price <= 0)
            {
                throw new ShopSysLogicalException("Product price can't be 0 or less");
            }
            if (amount <= 0)
            {
                throw new ShopSysLogicalException("Product amount can't be 0 or less");
            }
            
            Price = price;
            Amount = amount;
        }

    }
}