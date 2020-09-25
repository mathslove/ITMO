namespace lab2.ShopSystem.Exceptions
{
    public class ShopSysUnexpectedBehaviorException: ShopSysException
    {
        private const string DefaultM = "Shop System detected unexpected behavior!\n";
        public ShopSysUnexpectedBehaviorException(string m):
            base(DefaultM + m + "\n"){}
    }
}