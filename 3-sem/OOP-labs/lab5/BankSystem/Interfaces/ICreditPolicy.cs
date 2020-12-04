namespace lab5.BankSystem.Interfaces
{
    public interface ICreditPolicy
    {
        public double GetCommissionOnBalance(double balance);
    }
}