using lab2_pro.ShopSystem.Exceptions;

namespace lab2_pro.ShopSystem.Entities
{
    public class StockKeepingUnit: Product
    {
        private int price;
        private int amount;

        public StockKeepingUnit(int price, int amount, Product prod):
            base(prod)
        {
            this.price = price;
            this.amount = amount;
        }

        public int GetPrice()
        {
            return price;
        }
        
        public int GetAmount()
        {
            return amount;
        }

        public void AddAmount(int plus)
        {
            if (amount + plus > 0)
            {
                amount += plus;
            }else
                throw new ShopSysUnexpectedBehaviorException($"Given amount {plus} is bigger than current {amount}");
        }
        
    }
}