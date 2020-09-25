using System.Collections.Generic;
using lab2.ShopSystem.Containers;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem.Containers
{
    public class BatchForConsuming : Batch
    {
        public void Add(Product product, uint price, uint amount)
        {
            if (!BatchList.ContainsKey(product))
            {
                BatchList.Add(product, new ProductProp(price, amount));
            }
            else
            {
                if (BatchList[product].Price != price)
                {
                    throw new ShopSysUnexpectedBehaviorException("You can't add product and change its price if it's already exists in batch");
                }
                BatchList[product].Amount += amount;
            }
        }

        public Dictionary<Product, ProductProp> GetBatchList()
        {
            return BatchList;
        }

        public void Clean()
        {
            BatchList.Clear();
        }
    }
}