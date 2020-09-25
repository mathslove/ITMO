using System;
using System.Collections.Generic;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;
using lab2.ShopSystem.Containers;
using lab2.ShopSystem.Utils;

namespace lab2.ShopSystem
{
    public class ShopManager
    {
        private IdGenerator IG;
        private static List<Shop> _shopsList;
        
        public ShopManager()
        {
            _shopsList = new List<Shop>();
            IG = new IdGenerator();
        }

        public Shop Create(string shopName, string shopAddress)
        {
            var newShop = new Shop(id: IG.GenerateUniqId(),name: shopName, address: shopAddress);
            _shopsList.Add(newShop);
            return newShop;
        }

        public List<Shop> GetShopsList()
        {
            return _shopsList;
        }
        
        public Shop FindShopWithCheapestProduct(Product product)
        {
            if (_shopsList.Count == 0)
            {
                throw new ShopSysLogicalException("ShopsList list can't be empty");
            }
            
            var min = uint.MaxValue;
            Shop resShop = null;
            
            foreach (var shop in _shopsList)
            {
                if (shop[product].Price < min)
                {
                    min = shop[product].Price;
                    resShop = shop;
                }
            }

            if (resShop != null) 
                return resShop;
            else 
                throw new ShopSysException("");
        }


        public Shop GetShopWithLowestCostForBatch(BatchForBuying batch)
        {
            if (batch == null || batch.GetBatchList().Count == 0)
            {
                throw new ShopSysLogicalException("Batch can't be empty");
            }

            if (_shopsList.Count == 0)
            {
                throw new ShopSysLogicalException("ShopsList list can't be empty");
            }
            
            Shop resShop = null;
            uint min = uint.MaxValue;

            foreach (var shop in _shopsList)
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
                catch (Exception)
                {
                    // ignored
                }
            }
            
            return resShop;
        }

    }
}