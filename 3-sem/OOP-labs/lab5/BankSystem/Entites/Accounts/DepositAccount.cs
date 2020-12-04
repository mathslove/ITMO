using System;
using lab5.BankSystem.Exception;
using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites.Accounts
{
    public class DepositAccount:IAccount
    {
        private double _balance;
        private double _cashback;
        private int _days_limit;
        private int _cur_day;
        private IDepositPolicy _policy;
        private Guid _id;

        public DepositAccount(IDepositPolicy policy, double balance, int days)
        {
            _id = Guid.NewGuid();
            _days_limit = days;
            _cur_day = 0;
            _balance = balance;
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

        public void CashIn(double amount)
        {
            _balance += amount;
        }

        public void CashOut(double amount)
        {
            if (_cur_day<_days_limit)
                throw new BankSysException("Operation is impossible");
            if (amount>_balance)
                throw new BankSysException("Operation is impossible");
            _balance -= amount;

        }

        public double CalcDay()
        {
            _cur_day ++;
            _cashback += _balance * _policy.GetInterestOnBalance(_balance);
            return _cashback;
        }

        public double CalcPeriod()
        {
            var cashback = _cashback;
            _balance += _cashback;
            _cashback = 0;
            return cashback;
        }
    }
}