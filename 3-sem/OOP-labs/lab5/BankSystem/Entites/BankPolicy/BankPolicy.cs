using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    public class BankPolicy
    {
        public IDebitPolicy DebitPolicy { get; }
        public IDepositPolicy DepositPolicy { get; }
        public ICreditPolicy CreditPolicy { get; }
        public double SuspiciousLimit { get; private set; }

        public BankPolicy(IDebitPolicy debitPolicy, IDepositPolicy depositPolicy, ICreditPolicy creditPolicy)
        {
            DebitPolicy = debitPolicy;
            DepositPolicy = depositPolicy;
            CreditPolicy = creditPolicy;
        }

        public void SetLimitForSus(double limit)
        {
            SuspiciousLimit = limit;
        }
    }
}