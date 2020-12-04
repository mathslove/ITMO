using System;
using lab5.BankSystem.Exception;
using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites.Accounts
{
    public class CreditAccount: IAccount
    {
        private double _balance;
        private double _limit;
        private double _debt;
        private ICreditPolicy _policy;
        private Guid _id;
        public CreditAccount(ICreditPolicy policy, double limit)
        {
            _id = Guid.NewGuid();
            _balance = 0;
            _debt = 0;
            _policy = policy;
            _limit = limit;
        }

        public Guid GetId()
        {
            return _id;
        }

        public double GetAccountBalance()
        {
            return _balance;
        }

        public void CashIn(double amount)
        {
            _balance += amount;
        }

        public void CashOut(double amount)
        {
            if (-_limit > _balance - amount)
            {
                throw new BankSysException("Credit limit wasted");
            }

            _balance -= amount;
        }
        
        public double CalcDay()
        {
            if (_balance<0)
            {
                _debt -= -_balance * _policy.GetCommissionOnBalance(-_balance)/100;
            }

            return _debt;
        }

        public double CalcPeriod()
        {
            var debt = _debt;
            _balance += _debt;
            _debt = 0;
            return debt;
        }
    }
}