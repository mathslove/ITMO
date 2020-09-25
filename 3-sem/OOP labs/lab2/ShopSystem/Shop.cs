using System;
using System.Collections.Generic;
using lab2.ShopSystem.Containers;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Interface;
using lab2.ShopSystem.Types;

namespace lab2.ShopSystem
{
    public class Shop:IShop
    {
        public string Address { get;  }
        public uint Id { get; }
        public string Name { get; }
        private Dictionary<Product, ProductProp> Storage;

        public Shop(uint id, string name, string address)
        {
            Id = id;
            Name = name;
            Address = address;
            Storage = new Dictionary<Product, ProductProp>();
        }

        public ProductProp this[Product key]
        {
            get
            {
                if (Storage.ContainsKey(key))
                {
                    return Storage[key];
                }
                else
                {
                    throw new ShopSysUnexpectedBehaviorException(
                        $" Given product doesn't contains in shop id: {Id}\n name: {Name}\n address: {Address}");
                }
            } 
        }

        private void AddProduct(Product product, uint price, uint amount)
        {
            if (Storage.ContainsKey(product))
            {
                if (Storage[product].Price == price || price == uint.MaxValue)
                    Storage[product].Amount += amount;
                else
                    throw new ShopSysUnexpectedBehaviorException("You can't add product and change its price if it's already exists in shop");
            }
            else
            {
                if (price != uint.MaxValue)
                {
                    Storage.Add(product, new ProductProp(price, amount));
                }
                else
                {
                    throw  new ShopSysUnexpectedBehaviorException("Can't add product with such price: uint.MaxValue, reserved number");
                }
            }
        }

        private void AddProduct(Product product, ProductProp prop)
        {
            AddProduct(product, prop.Price, prop.Amount);
        }

        private void BuyProduct(Product product, uint amount)
        {
            if (Storage.ContainsKey(product))
            {
                if (Storage[product].Amount >= amount)
                {
                    Storage[product].Amount -= amount;
                }
                else
                {
                    throw new ShopSysUnexpectedBehaviorException($"We don't have enough amount of this product: {product.Name} / {product.Id}");
                }
            }
            else
            {
                throw new ShopSysUnexpectedBehaviorException(
                    $"We don't have this product {product.Name} / {product.Id}");
            }
        }

        public void ChangeProductPrice(Product product, uint price)
        {
            if (price <= 0) throw new ShopSysLogicalException("Price can't be 0 or lower");
            
            if (Storage.ContainsKey(product))
            {
                Storage[product].Price = price;
            }
            else
            {
                throw new ShopSysLogicalException($"Product doesn't exist in current shop id: {Id} name:{Name}");
            }
        }
        
        public void ConsumeBatch(BatchForConsuming batch)
        {
            try
            {
                foreach (var product in batch.GetBatchList())
                {
                    AddProduct(product.Key, product.Value);
                }
            }
            catch (ShopSysUnexpectedBehaviorException e)
            {
                Console.Write(e.Message);
                throw;
            }

        }

        public uint BuyBatch(BatchForBuying batch)
        {
            try
            {
                uint sum = 0;
                foreach (var (product, amount) in batch.GetBatchList())
                {
                    BuyProduct(product, amount);
                    sum += Storage[product].Price * amount;
                }

                return sum;
            }
            catch (ShopSysUnexpectedBehaviorException e)
            {
                Console.Write(e.Message);
                throw;
            }
        }
        
        public Dictionary<Product,ProductProp> GetAll()
        {
            return Storage;
        }

        public Dictionary<Product, uint> GetProductsAmountForBudget(uint budget)
        {
            var res = new Dictionary<Product, uint>();
            
            foreach (var (product, prop) in Storage)
            {
                var maxAmount = budget / prop.Price;
                if (maxAmount <= prop.Amount)
                {
                    res.Add(product, maxAmount);
                }
                else
                {
                    res.Add(product, prop.Amount);
                }
            }

            return res;
        }

        public uint CalcBatchCost(BatchForBuying batch)
        {
            uint sum = 0;
            
            foreach (var (product, amount) in batch.GetBatchList())
            {
                if (Storage.ContainsKey(product))
                {
                    if (Storage[product].Amount >= amount)
                    {
                        sum += Storage[product].Price * amount;
                    }
                    else
                    {
                        throw new ShopSysUnexpectedBehaviorException($"Not enough product in the shop {amount} / {Storage[product].Amount}");
                    }
                }
                else
                {
                    throw new ShopSysUnexpectedBehaviorException($"There is not such product in the shop {product.Name} / {product.Id}");
                }
                
            }

            return sum;
        }
        
        
    }
}