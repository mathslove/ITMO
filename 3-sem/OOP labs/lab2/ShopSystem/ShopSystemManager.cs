using System;
using System.Collections.Generic;
using lab2.ShopSystem.Exceptions;
using lab2.ShopSystem.Types;
using lab2.ShopSystem.Containers;
using lab2.ShopSystem.Utils;

namespace lab2.ShopSystem
{
    public class ShopSystemManager
    {
        private IdGenerator _idGeneratorShops;
        private IdGenerator _idGeneratorProducts;
        private static List<Shop> _shopsList;
        private static List<Product> _productsList;
        private static List<BatchForConsuming> _batchForConsumingsList;
        private static List<BatchForBuying> _batchForBuyingList;
        public ShopSystemManager()
        {
            _shopsList = new List<Shop>();
            _productsList = new List<Product>();
            _idGeneratorShops = new IdGenerator();
            _idGeneratorProducts = new IdGenerator();
            _batchForConsumingsList = new List<BatchForConsuming>();
            _batchForBuyingList = new List<BatchForBuying>();
        }

        public int CreateShop(string shopName, string shopAddress)
        {
            var newShop = new Shop(id: _idGeneratorShops.GenerateUniqId(),name: shopName, address: shopAddress);
            _shopsList.Add(newShop);
            
            return _shopsList.Count - 1;
        }

        public string GetShopByID(uint shopId)
        {
            try
            {
                foreach (var shop in _shopsList)
                {
                    if (shop.Id == shopId) return "This is the shop with given ID:\n"
                                                  +$"{shop.Id} {shop.Name} {shop.Address}";
                }
                throw new ShopSysException($"No shop with such ID {shopId} was found");
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        public void ShopProductPriceChange(int shopIndex, int productIndex, uint newPrice)
        {
            try
            {
                _shopsList[shopIndex].ChangeProductPrice(_productsList[productIndex], newPrice);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
        
        public void ShopConsumeBatch(int shopIndex, int batchIndex)
        {
            try
            {
                _shopsList[shopIndex].ConsumeBatch(_batchForConsumingsList[batchIndex]);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        public string ShopBuyBatch(int shopIndex, int batchIndex)
        {
            try
            {
                return "This is the money you spent for given cart:\n"+_shopsList[shopIndex].BuyBatch(_batchForBuyingList[batchIndex]).ToString();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }
        
        public int CreateProduct(string productName)
        {
            var newProduct = new Product(id: _idGeneratorProducts.GenerateUniqId(),name: productName);
            _productsList.Add(newProduct);
            
            return _productsList.Count - 1;
        }

        public int CreateBatchForConsuming()
        {
            _batchForConsumingsList.Add(new BatchForConsuming());
            return _batchForConsumingsList.Count - 1;
        }

        public void BatchForConsumingAdd(int batchIndex, int productIndex, uint price, uint amount)
        {
            try
            {
                _batchForConsumingsList[batchIndex].Add(_productsList[productIndex], price, amount);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        public int CreateBatchForBuying()
        {
            _batchForBuyingList.Add(new BatchForBuying());
            return _batchForBuyingList.Count - 1;
        }
        
        public void BatchForBuyingAdd(int batchIndex, int productIndex,uint amount)
        {
            try
            {
                _batchForBuyingList[batchIndex].Add(_productsList[productIndex], amount);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
        
        public string GetShopWithCheapestProduct(int productIndex)
        {
            try
            {
                var product = _productsList[productIndex];
                if (_shopsList.Count == 0)
                {
                    throw new ShopSysLogicalException("ShopsList list can't be empty");
                }

                var min = uint.MaxValue;
                Shop resShop = null;

                foreach (var shop in _shopsList)
                {
                    try
                    {
                        if (shop[product].Price <= min)
                        {
                            min = shop[product].Price;
                            resShop = shop;
                        }
                    }
                    catch (Exception)
                    {
                        // ignored
                    }
                }

                if (resShop != null)
                    return $"This shop provides lowest price for given product{product.Name}\n" +
                           ""+$"{resShop.Id} {resShop.Name} {resShop.Address}";
                else
                    throw new ShopSysException("GetShopWithCheapestProduct: No shop was found");
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }


        public string GetShopWithLowestCostForBatch(int batchIndex)
        {
            try
            {
                var batch = _batchForBuyingList[batchIndex];
                if (batch == null || batch.GetBatchList().Count == 0)
                {
                    throw new ShopSysLogicalException("Batch can't be empty");
                }

                if (_shopsList.Count == 0)
                {
                    throw new ShopSysLogicalException("ShopsList list can't be empty");
                }

                Shop resShop = null;
                var min = uint.MaxValue;

                foreach (var shop in _shopsList)
                {
                    try
                    {
                        var cur = shop.CalcBatchCost(batch);
                        if (cur >= min) continue;
                        min = cur;
                        resShop = shop;
                    }
                    catch (Exception)
                    {
                        // ignored
                    }
                }

                if (resShop != null)
                    return $"This is the shop with lowest cost for given cart\n" +
                           $"{resShop.Id} {resShop.Name} {resShop.Address}";
                else
                    throw new ShopSysException("GetShopWithLowestCostForBatch: No shop was found");
            }
            catch(Exception e)
            {
                return e.Message;
            }
        }

        public string GetProductsAmountForBudgetInShop(int shopIndex, uint budget)
        {
            try
            {
                var res = _shopsList[shopIndex].GetProductsAmountForBudget(budget);
                var resS = string.Empty;
                foreach (var (product, amount) in res)
                {
                    resS += $"{product.Name} (id: {product.Id}) in amount of {amount}\n";
                }

                if (resS != string.Empty)
                {
                    return $"That are products that you are able to buy for {budget} in our shop {_shopsList[shopIndex].Name}:\n"
                           +resS;
                }
                else
                {
                    return
                        $"You can buy nothing in this shop {_shopsList[shopIndex].Name}({_shopsList[shopIndex].Id}) for such budget {budget}\n";
                }
            }
            catch(Exception e)
            {
                return "GetProductsAmountForBudgetInShop:\n"
                    +e.Message;
            }
        }

    }
}