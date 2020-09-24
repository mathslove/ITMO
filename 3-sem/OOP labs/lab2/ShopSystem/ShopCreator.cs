using System.Collections.Generic;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem
{
    public class ShopCreator
    {
        private static List<Shop> ShopsList;
        
        public ShopCreator()
        {
            ShopsList = new List<Shop>();
        }

        public Shop Create(string shopName, string shopAddress)
        {
            var newShop = new Shop(name: shopName, address: shopAddress);
            ShopsList.Add(newShop);
            return newShop;
        }

        public List<Shop> GetShopsList()
        {
            return ShopsList;
        }

    }
}