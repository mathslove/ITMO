namespace lab2_2.ShopSystem.Exceptions
{
    public class ShopSysException: System.Exception
    {
        private const string DefaultM = "Shop System has failed! \n";
        
        public ShopSysException(string m):
            base(DefaultM + m + "\n"){}
    }
}