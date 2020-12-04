namespace lab5.BankSystem.Exception
{
    public class BankSysException:System.Exception
    {
        private const string DefaultM = "Shop System has failed! \n";
        
        public BankSysException(string m):
            base(DefaultM + m + "\n"){}
    }
}