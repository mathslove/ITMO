using System;
using System.Collections.Generic;
using lab5.BankSystem.Entites.Accounts;
using lab5.BankSystem.Exception;
using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    using ClientId = System.Guid;
    using AccountId = System.Guid;
    using TransactionId = System.Guid;
    public partial class Bank
    {
        public enum OperationTYPE
        {
            CASH_OUT,
            CASH_IN,
            TRANSFER
        }
        
        //Info
        private string _name;
        private System.Guid _id;
        private DateTime _innerTime;
        
        //Это типо было бы всё в бд, но пока вот так
        private Dictionary<ClientId,Client> _clients;
        private Dictionary<AccountId,IAccount> _accounts;
        private Dictionary<ClientId, List<AccountId>> _dependencies;
        private Dictionary<TransactionId, Transaction> _transactions;
        //
        private BankPolicy _policy;
        private Verifier _guard;
        
        public Bank(string name,BankPolicy policy)
        {
            _name = name;
            _id = Guid.NewGuid();
            _innerTime = DateTime.Now;
            
            _policy = policy;
            _guard = new Verifier(this);
            _guard.SetSusLimit(_policy.SuspiciousLimit);
            
            _clients = new Dictionary<Guid, Client>();
            _accounts = new Dictionary<Guid, IAccount>();
            _dependencies = new Dictionary<Guid, List<AccountId>>();
            _transactions = new Dictionary<Guid, Transaction>();
        }

        public ClientId AddClient(Client client)
        {
            if (!_guard.VerifyClient(client.GetId()))
            {
                _clients.Add(client.GetId(), client);
            }
            throw new BankSysException("Such client already exists in this bank");
        }

        public AccountId CreateDebitAccount(ClientId client)
        {
            if (!_guard.VerifyClient(client))
            {
                throw new BankSysException("No such client");
            }
            
            var account = new DebitAccount(_policy.DebitPolicy);
            _accounts.Add(account.GetId(), account);
            _dependencies[client].Add(account.GetId());
            return account.GetId();
        }
        
        public AccountId CreateDepositAccount(ClientId client,double balance, int days)
        {
            if (!_guard.VerifyClient(client))
            {
                throw new BankSysException("No such client");
            }
            
            var account = new DepositAccount(_policy.DepositPolicy,balance,days);
            _accounts.Add(account.GetId(), account);
            _dependencies[client].Add(account.GetId());
            return account.GetId();
        }
        
        public AccountId CreateCreditAccount(ClientId client, double limit)
        {
            if (!_guard.VerifyClient(client))
            {
                throw new BankSysException("No such client");
            }
            
            var account = new CreditAccount(_policy.CreditPolicy, limit);
            _accounts.Add(account.GetId(), account);
            _dependencies[client].Add(account.GetId());
            return account.GetId();
        }

        public TransactionId CashIn(ClientId client, AccountId account, double amount)
        {
            if(_guard.VerifyClient(client))
                throw new BankSysException("Client wasn't verified in the bank");
            if (_guard.VerifyAccount(client, account))
                throw new BankSysException("Account wasn't verified in the bank");

            _guard.VerifyOperation(client, OperationTYPE.CASH_IN, amount);
            try
            {
                _accounts[account].CashIn(amount);
            }
            catch (BankSysException e)
            {
                throw new BankSysException("Can't cash-in to account");
            }

            var tr = new Transaction(OperationTYPE.CASH_IN,client,account,amount);
            _transactions.Add(tr.Id,tr);
            return tr.Id;
        }

        public TransactionId CashOut(ClientId client, AccountId account, double amount)
        {
            if(_guard.VerifyClient(client))
                throw new BankSysException("Client wasn't verified in the bank");
            if (_guard.VerifyAccount(client, account))
                throw new BankSysException("Account wasn't verified in the bank");
            
            _guard.VerifyOperation(client, OperationTYPE.CASH_OUT, amount);
            try
            {
                _accounts[account].CashOut(amount);
            }
            catch (BankSysException e)
            {
                throw new BankSysException("Can't cash-out from account");;
            }
            
            var tr = new Transaction(OperationTYPE.CASH_OUT,client,account,amount);
            _transactions.Add(tr.Id,tr);
            return tr.Id;
            
        }


        public TransactionId Transfer(double amount, ClientId client1, AccountId account1, ClientId client2, AccountId account2,
            Bank bank = null)
        {
            bank ??= this;
            
            if(_guard.VerifyClient(client1))
                throw new BankSysException("Client wasn't verified in the bank");
            if (_guard.VerifyAccount(client1, account1))
                throw new BankSysException("Account wasn't verified in the bank");
            
            if(bank._guard.VerifyClient(client2))
                throw new BankSysException("Client wasn't verified in the bank");
            if (bank._guard.VerifyAccount(client2, account2))
                throw new BankSysException("Account wasn't verified in the bank");

            var IsCashedOut=false;
            try
            {
                _accounts[account1].CashOut(amount);
                IsCashedOut = true;
                bank._accounts[account2].CashIn(amount);
            }
            catch (BankSysException e)
            {
                if (IsCashedOut)
                {
                    _accounts[account1].CashIn(amount);
                }
                throw new BankSysException("Can't transfer money to another bank");
            }
            
            var tr = new Transaction(OperationTYPE.TRANSFER,client1,account1,client2,account2,amount);
            _transactions.Add(tr.Id,tr);
            return tr.Id;
            
        }

        public void CancelOperation(TransactionId transaction)
        {
            if (_guard.VerifyTransaction(transaction))
            {
                throw new BankSysException("Such transaction ia absent in the bank");
            }

            var tr = _transactions[transaction];
            switch (tr.Operation)
            {
                case OperationTYPE.CASH_IN:
                    CashOut(tr.Client,tr.Account,tr.Amount);
                    break;
                case OperationTYPE.CASH_OUT:
                    CashIn(tr.Client,tr.Account,tr.Amount);
                    break;
                case OperationTYPE.TRANSFER:
                    CashIn(tr.Client,tr.Account,tr.Amount);
                    CashOut(tr.Client2, tr.Account2, tr.Amount);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public void CalcDay()
        {
            var month_end = _innerTime.Day==DateTime.DaysInMonth(_innerTime.Year, _innerTime.Month);
            foreach (var account in _accounts)
            {
                account.Value.CalcDay();
                if (month_end)
                {
                    account.Value.CalcPeriod();
                }
            }
        }

        public void MoveInTime(int days)
        {
            for (var i = 0; i < days; i++)
            {
                CalcDay();
            }
        }
        

    }
}