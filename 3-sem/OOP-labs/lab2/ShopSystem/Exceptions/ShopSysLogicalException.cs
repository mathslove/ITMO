namespace lab2_pro.ShopSystem.Exceptions
{
    public class ShopSysLogicalException: ShopSysException
    {
        private const string DefaultM = "Shop System detected logical error!\n";
        public ShopSysLogicalException(string m):
            base(DefaultM + m + "/n"){}
    }
}