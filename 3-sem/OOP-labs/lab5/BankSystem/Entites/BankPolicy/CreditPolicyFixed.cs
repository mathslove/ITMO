using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    public class CreditPolicyFixed:ICreditPolicy
    {
        private double _commission;
        public void SetCommission(double commission)
        {
            _commission = commission;
        }
        public double GetCommissionOnBalance(double balance)
        {
            return _commission;
        }
    }
}