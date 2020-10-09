using System;
using System.Collections;
using System.Collections.Generic;
using lab2_pro.ShopSystem.Interface;

namespace lab2_pro.ShopSystem.Entities
{
    public class Repository: IShopSysRepository
    {
        private Dictionary<uint, Shop> _shops;
        private Dictionary<uint, Product> _products;

        public bool AddShop(Shop shop)
        {
            if (_shops.ContainsKey(shop.GetId()))
            {
                return false;
            }
            else
            {
                _shops.Add(shop.GetId(), shop);
            }

            return true;
        }

        public bool AddProduct(Product prod)
        {
            if (_products.ContainsKey(prod.GetId()))
            {
                return false;
            }
            else
            {
                _products.Add(prod.GetId(), prod);
            }

            return true;
        }
        
        public List<Shop> GetAllShops()
        {
            List<Shop> shops = new List<Shop>();
            foreach (var (id,shop) in _shops)
            {
                shops.Add(shop);
            }
            return shops;
        }

        public List<Product> GetAllProducts()
        {
            List<Product> products = new List<Product>();
            foreach (var (id,prod) in _products)
            {
                products.Add(prod);
            }
            return products;
        }

        public Shop FinShopById(uint id)
        {
            if (_shops.ContainsKey(id))
            {
                return _shops[id];
            }
            else
            {
                return null;
            }
        }

        public Product FindProductById(uint id)
        {
            if (_products.ContainsKey(id))
            {
                return _products[id];
            }
            else
            {
                return null;
            }
        }
    }
}