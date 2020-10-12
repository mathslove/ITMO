using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace lab2_pro.ShopSystem.Entities
{
    public class Cart
    {
        private Dictionary<Product, int> my_cart;

        public Cart()
        {
            my_cart = new Dictionary<Product, int>();
        }

        public bool Add(int amount, Product prod)
        {
            if (amount<0)
            {
                return false;
            }
            
            if (my_cart.ContainsKey(prod))
            {
                my_cart[prod] += amount;
            }
            else
            {
                my_cart.Add(prod, amount);
            }
            return true;
        }

        public Dictionary<Product, int> GetAll()
        {
            return my_cart;
        }

        public void Clear()
        {
            my_cart.Clear();
        }
    }
}