using System.Collections.Generic;
using lab2.ShopSystem.Containers;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem.Containers
{
    public class BatchForBuying : Batch
    {
        public BatchForBuying() {}

        public void Add(Product product,uint amount)
        {
            if (!BatchList.ContainsKey(product))
            {
                BatchList.Add(product, new ProductProp(uint.MaxValue, amount));
            }
            else
            {
                BatchList[product].Amount += amount;
            }
        }

        public Dictionary<Product, uint> GetBatchList()
        {
            var res = new Dictionary<Product, uint>();

            foreach (var (product, prop) in BatchList)
            {
                res.Add(product, prop.Amount);
            }
            
            return res;
        }
        
    }
}