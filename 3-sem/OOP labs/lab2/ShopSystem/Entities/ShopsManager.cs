using System;
using System.Collections.Generic;

namespace lab2_pro.ShopSystem.Entities
{
    public class ShopsManager
    {
        public ShopsManager() {}

        public Shop GetShopWithCheapestProduct(Product prod, Repository rep)
        {
            var min = Int32.MaxValue;
            Shop resShop = null;
            var shops = rep.GetAllShops();
            
            foreach (var  shop in shops)
            {
                if (shop.GetProductPrice(prod, out var cur))
                {
                    if (cur<min)
                    {
                        min = cur;
                        resShop = shop;
                    }
                }
            }

            return resShop;
        }

        public Shop GetShopWithCheapestCart(Cart cart, Repository rep)
        {
            Shop resShop = null;
            var shops = rep.GetAllShops();

            int cost;
            int min = Int32.MaxValue;
            foreach (var shop in shops)
            {
                if (shop.GetCartCost(cart, out cost))
                {
                    if (min > cost)
                    {
                        min = cost;
                        resShop = shop;
                    }
                }
            }
            
            return resShop;
        }
    }
}