using System.Collections;
using System.Collections.Generic;
using lab2_pro.ShopSystem.Entities;

namespace lab2_pro.ShopSystem.Interface
{
    public interface IShopSysRepository
    {
        public bool AddShop(Shop shop);
        public bool AddProduct(Product prod);
        public List<Shop> GetAllShops();
        public List<Product> GetAllProducts();

        public Shop FinShopById(uint id);
        public Product FindProductById(uint id);

    }
}