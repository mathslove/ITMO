using System;
using lab5.BankSystem.Exception;
using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites.Accounts
{
    public class DebitAccount: IAccount
    {
        private double _balance;
        private double _cashback;
        private IDebitPolicy _policy;
        private Guid _id;

        public DebitAccount() { }
        public DebitAccount(IDebitPolicy policy)
        {
            _id = Guid.NewGuid();
            _balance = 0;
            _cashback = 0;
            _policy = policy;
        }

        public Guid GetId()
        {
            return _id;
        }

        public double GetAccountBalance()
        {
            return _balance;
        }
        

        public void CashIn(double amount)//noexcept
        {
            _balance += amount;
        }
        
        public void CashOut(double amount)
        {
            if (amount > _balance)
            {
                throw new BankSysException("Not enough money on account");
            }
            _balance -= amount;
        }

        public double CalcDay()
        {
            _cashback += _balance * _policy.GetInterestOnBalance(_balance) / 100;
            return _cashback;
        }
        
        public double CalcPeriod()
        {
            var cash = _cashback;
            _balance += _cashback;
            _cashback = 0;
            return cash;
        }
    }
}