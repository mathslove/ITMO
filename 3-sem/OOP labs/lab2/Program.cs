using System;
using lab2.ShopSystem;

namespace lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            // Самый user-friendly интерфейс, как  просили
            
            
            // Создаём 3 магаза и 10 продуктов, всё через мендежр!!! Никаких инстантсов классов кроме менеджера!!!
            var smanager = new ShopSystemManager();
            var s1 = smanager.CreateShop("Sample1", "USA");
            var s2 = smanager.CreateShop("Sample2", "Mexico");
            var s3 = smanager.CreateShop("Sample3", "USA");
 
            var products = new int[10];
            for (int i = 0; i < products.Length; i++)
            {
                products[i] = smanager.CreateProduct($"Product Sample{i}");
            }
 
            // Добовляем товары в патрию доставки и пушим в магазин
            var batch1 = smanager.CreateBatchForConsuming();
 
            for (int i = 0; i < 5; i++)
                smanager.BatchForConsumingAdd(batch1,products[i], (uint) (5 + i), 10);
 
            smanager.ShopConsumeBatch(s1,batch1);
 
            var batch2 = smanager.CreateBatchForConsuming();            
            for (int i = 0; i < 5; i++)
                smanager.BatchForConsumingAdd(batch2,products[i+5], (uint) (5 + i), 10);
 
            smanager.ShopConsumeBatch(s2,batch2); 
            
            var batch3 = smanager.CreateBatchForConsuming();
            for (int i = 0; i < 10; i++)
                smanager.BatchForConsumingAdd(batch3,products[i], (uint) (5 + i), 10);
 
            smanager.ShopConsumeBatch(s3,batch3);
            
            // Найдём магазин где можно купить хлеб по дешёвке
            Console.WriteLine(smanager.GetShopWithCheapestProduct(products[0]));
            Console.WriteLine();


            // Найдём что мы можем купить в данном магазине на 100 рубликов
            Console.WriteLine(smanager.GetProductsAmountForBudgetInShop(s1, 100));
            Console.WriteLine();

            // Купим партию товаров в магазине
            var cart = smanager.CreateBatchForBuying();
            smanager.BatchForBuyingAdd(cart, products[1], 2);
            smanager.BatchForBuyingAdd(cart, products[4], 2);
            
            Console.WriteLine(smanager.ShopBuyBatch(s1,cart));
            Console.WriteLine();
            
            // Найдём в каком магазине партия товаров имеет наименьшую сумму

            Console.WriteLine(smanager.GetShopWithLowestCostForBatch(cart));
            Console.WriteLine();
            
            //
            //На этом всё, если поймал исключение, значит вкинул не то или не туда, будь осторожен
            //
        }
    }
}