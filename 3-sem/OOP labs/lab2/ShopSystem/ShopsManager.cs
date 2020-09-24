using System;
using System.Collections.Generic;
using System.Linq;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem
{
    public class ShopsTaskManager
    {
        /*private static List<Shop> ShopsList;*/

        public ShopsTaskManager()
        {}
        
        /*public ShopsTaskManager(List<Shop> shops)
        {
            UpdateShops(shops);
        }

        public void UpdateShops(List<Shop> shops)
        {
            if (shops.Count == 0)
            {
                throw new ShopSysLogicalException("");
            }
            ShopsList = shops;
        }
        
        public Shop FindShopWithCheapestProduct(Product product)
        {
            var min = uint.MaxValue;
            Shop resShop = null;
            
            foreach (var shop in ShopsList)
            {
                if (shop[product].Price < min)
                {
                    min = shop[product].Price;
                    resShop = shop;
                }
            }

            return resShop;
        }*/
        
        public Shop FindShopWithCheapestProduct(Product product, List<Shop> shops)
        {
            if (shops.Count == 0)
            {
                throw new ShopSysLogicalException("Shops list can't be empty");
            }
            
            var min = uint.MaxValue;
            Shop resShop = null;
            
            foreach (var shop in shops)
            {
                if (shop[product].Price < min)
                {
                    min = shop[product].Price;
                    resShop = shop;
                }
            }

            return resShop;
        }


        public Shop GetShopWithLowestCostForBatch(BatchForBuying batch, List<Shop> shops)
        {
            if (batch == null || batch.GetBatchList().Count == 0)
            {
                throw new ShopSysLogicalException("Batch can't be empty");
            }

            if (shops.Count == 0)
            {
                throw new ShopSysLogicalException("Shops list can't be empty");
            }
            
            Shop resShop = null;
            uint min = uint.MaxValue;

            foreach (var shop in shops)
            {
                try
                {
                    var cur = shop.CalcBatchCost(batch);
                    if (cur < min)
                    {
                        min = cur;
                        resShop = shop;
                    }

                    
                }
                catch (Exception e)
                {
                    continue;
                }
            }
            
            return resShop;
        }
        
    }
}