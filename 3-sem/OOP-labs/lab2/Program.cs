using System;
using lab2_pro.ShopSystem.Entities;

namespace lab2_pro
{
    class Program
    { 
        static void Main(string[] args)
        {
            var rep = new Repository();
            
            var shop1 = new Shop("Лента", "Колотушкино");
            rep.AddShop(shop1);
            
            var shop2 = new Shop("5-очка", "Пушкино");
            rep.AddShop(shop2);
            
            var shop3 = new Shop("Эрос", "Небеса");
            rep.AddShop(shop3);

            var pr = new Product[10];
            for (int i = 0; i < 10; i++)
            {
                pr[i] = new Product($"{i}-ый продукт");
            }

            shop1.AddProduct(10, 228, pr[0]);
            shop1.AddProduct(10, 50, pr[1]);
            
            shop2.AddProduct(10, 322, pr[0]);
            shop2.AddProduct(5, 1488, pr[1]);
            shop2.AddProduct(3, 1812, pr[2]);
            
            shop3.AddProduct(10, 322, pr[0]);
            shop3.AddProduct(5, 1488, pr[1]);
            shop3.AddProduct(3, 1812, pr[2]);
            shop3.AddProduct(100, 1945, pr[9]);
            
            var man = new ShopsManager();
            
            var res = man.GetShopWithCheapestProduct(pr[0], rep);
            Console.WriteLine(res.GetName());

            var resl = shop2.GetProductsForBudget(100);
            foreach (var (prod, amount) in resl)
            {
                Console.WriteLine(prod.GetName());
            }

            var cart = new Cart();
            cart.Add(2, pr[0]);
            cart.Add(4, pr[1]);

            if (shop2.BuyCart(cart))
            {
                Console.WriteLine("U successfully bought cart");
            }
            else
            {
                Console.WriteLine("U unsuccessfully bought cart");
            }

            var res1 = man.GetShopWithCheapestCart(cart, rep);
            Console.WriteLine(res1.GetName());
        }
    }
}