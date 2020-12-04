using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    public class DebitPolicyFixed: IDebitPolicy
        {
            private double _interest;

            public void SetInterest(double interest)
            {
                _interest = interest;
            }
            
            public double GetInterestOnBalance(double balance)
            {
                return _interest;
            }
        }
}