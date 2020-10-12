using System;
using System.Collections.Generic;
using lab2_pro.ShopSystem.Exceptions;
using lab2_pro.ShopSystem.Interface;

namespace lab2_pro.ShopSystem.Entities
{
    public class Shop: IShop
    {
        private string Address;
        private uint Id;
        private string Name;

        private ShopData _storage;

        public Shop(string name, string address)
        {
            _storage = new ShopData();
            
            Name = name;
            Address = address;

            Id = (uint)GetHashCode();
        }

        public uint GetId()
        {
            return Id;
        }

        public string GetName()
        {
            return Name;
        }

        public string GetAddress()
        {
            return Address;
        }
        

//------------------------------------------------------------------------------------------
        public bool AddProduct(int amount, int price, Product prod)
        {
            try
            {
                _storage.Add( price,amount, prod);
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return false;
            }
        }

        private bool BuyProduct(int amount, Product prod)
        {
            try
            {
                _storage.Subtract(amount, prod);
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return false;
            }
        }

        public bool BuyCart(Cart cart)
        {
            try
            {

                foreach (var (prod, amount) in cart.GetAll())
                {
                    if (amount > _storage[prod.GetId()].GetAmount())
                    {
                        throw new ShopSysLogicalException("Не хватает");
                    }
                }
                
                foreach (var (prod, amount) in cart.GetAll())
                {
                    BuyProduct(amount, prod);
                }

                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return false;
            }
        } 
//------------------------------------------------------------------------------------------        

        public bool GetProductPrice(Product prod, out int price)
        {
            var p = _storage.GetProductById(prod.GetId());
            if (p != null)
            {
                price =  p.GetPrice();
                return true;
            }

            price = 0;
            return false;
        }

        public bool GetCartCost(Cart cart, out int cost)
        {
            cost = 0;
            foreach (var (prod , amount) in cart.GetAll())
            {
                if (_storage[prod.GetId()]!=null)
                {
                    if (amount <= _storage[prod.GetId()].GetAmount())
                    {
                        cost += amount * _storage[prod.GetId()].GetPrice();
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

        public List<KeyValuePair<Product, int>> GetProductsForBudget(int budget)
        {
            if (budget < 0)
            {
                return null;
            }

            var list = new List<KeyValuePair<Product, int>>();

            foreach (StockKeepingUnit prod in _storage)
            {
                var price = prod.GetPrice();
                var amount = prod.GetAmount();
                if (budget/price > amount)
                {
                    var pair = new KeyValuePair<Product, int>(new Product(prod.GetId(), prod.GetName()), amount);
                    list.Add(pair);
                }
                else
                {
                    var pair = new KeyValuePair<Product, int>(new Product(prod.GetId(), prod.GetName()), budget/price);
                    list.Add(pair);
                }
            }

            return list;
        }

    }
}