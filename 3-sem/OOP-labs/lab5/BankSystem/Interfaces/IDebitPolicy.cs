using System.Dynamic;

namespace lab5.BankSystem.Interfaces
{
    public interface IDebitPolicy
    {
        public double GetInterestOnBalance(double balance);
    }
}