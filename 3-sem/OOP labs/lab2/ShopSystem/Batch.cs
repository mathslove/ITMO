using System;
using System.Collections.Generic;
using System.Runtime;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem
{
    public class Batch
    {
        protected Dictionary<Product, ProductProp> BatchList;

        protected Batch()
        {
            BatchList = new Dictionary<Product, ProductProp>();
        }
    }

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
    }
}
