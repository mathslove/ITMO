using System;
using lab2.ShopSystem;

namespace lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            var smanager = new ShopSystemManager();
            var s1 = smanager.CreateShop("Sample1", "USA");
            var s2 = smanager.CreateShop("Sample2", "Mexico");
            var s3 = smanager.CreateShop("Sample3", "USA");
 
            var products = new int[10];
            for (int i = 0; i < products.Length; i++)
            {
                products[i] = smanager.CreateProduct($"Product Sample{i}");
            }
 
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
 
            smanager.ShopConsumeBatch(s3,batch3);        }
    }
}