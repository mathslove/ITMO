namespace lab5.BankSystem.Interfaces
{
    public interface IDepositPolicy
    {
        public double GetInterestOnBalance(double balance);
    }
}