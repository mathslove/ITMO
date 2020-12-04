namespace lab5.BankSystem.Interfaces
{ 
    using AccountId = System.Guid;
    public interface IAccount
    {
        public AccountId GetId();
        public double GetAccountBalance();
        public void CashIn(double amount);
        public void CashOut(double amount);
        public double CalcDay();
        public double CalcPeriod();
    }
}