namespace lab2_pro.ShopSystem.Exceptions
{
    public class ShopSysRuntimeErrorException: ShopSysException
    {
        private const string DefaultM = "Shop System detected logical error!\n";
        public ShopSysRuntimeErrorException(string m):
            base(DefaultM + m + "/n"){}
    }
}