using System.Collections;
using System.Collections.Generic;
using lab2_pro.ShopSystem.Exceptions;

namespace lab2_pro.ShopSystem.Entities
{
    public class ShopData: IEnumerable
    {
        private Dictionary<uint, StockKeepingUnit> _storage;

        public ShopData()
        {
            _storage = new Dictionary<uint, StockKeepingUnit>();
        }

        public IEnumerator GetEnumerator() {
            foreach (var (id, prod) in _storage)
            {
                yield return prod;
            }
        }

        public StockKeepingUnit this[uint id]
        {
            get
            {
                if (_storage.ContainsKey(id))
                {
                    return _storage[id];
                }
                else
                {
                    return null;
                }
            }
        }

        public void Add( int price,int amount, Product prod)
        {
            
            if (amount < 0)
            {
                throw new ShopSysUnexpectedBehaviorException($"Given amount {amount} can't be negative");
            }
            
            if (_storage.ContainsKey(prod.GetId()))
            {
                if (_storage[prod.GetId()].GetPrice() != price)
                {
                    throw new ShopSysUnexpectedBehaviorException($"This product {prod.GetName()} already exists with price {_storage[prod.GetId()].GetPrice()}");
                }
                else
                {
                    _storage[prod.GetId()].AddAmount(amount);
                }
            }
            else
            {
                _storage.Add(prod.GetId(), new StockKeepingUnit(price, amount, prod));
            }
        }

        public void Subtract(int amount, Product prod)
        {
            if (amount < 0)
            {
                throw new ShopSysUnexpectedBehaviorException($"Given amount {amount} can't be negative");
            }
            
            if (_storage.ContainsKey(prod.GetId()))
            {
                _storage[prod.GetId()].AddAmount(-amount);
            }
            else
            {
                throw new ShopSysLogicalException($"This product {prod.GetName()} doesn't exist in this shop");
            }
        }

        public StockKeepingUnit GetProductById(uint id)
        {
            if (_storage.ContainsKey(id))
            {
                return _storage[id];
            }
            else
            {
                return null;
            }
        }
    }
}