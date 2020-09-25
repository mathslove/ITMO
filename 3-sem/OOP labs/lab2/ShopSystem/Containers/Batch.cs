using System.Collections.Generic;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem.Containers
{
    public class Batch
    {
        protected Dictionary<Product, ProductProp> BatchList;

        protected Batch()
        {
            BatchList = new Dictionary<Product, ProductProp>();
        }
    }
}
