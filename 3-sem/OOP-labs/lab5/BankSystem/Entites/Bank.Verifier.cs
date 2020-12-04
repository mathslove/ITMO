using System;
using lab5.BankSystem.Exception;

namespace lab5.BankSystem.Entites
{
    using ClientId = System.Guid;
    using AccountId = System.Guid;
    using TransactionId = System.Guid;

    public partial class Bank
    {
         internal class Verifier
         {
             private Bank _guardedBank;
            private double _susLimits;
        
            public Verifier(Bank bank)
            {
                _guardedBank = bank;
                _susLimits = Double.NaN;
            }

            public void SetSusLimit(double limit)
            {
                _susLimits = limit;
            }

            public void EnsureOperation(ClientId clientId, OperationTYPE operation, double amount)
            {
                bool res;
                if (double.IsNaN(_susLimits))
                {
                    throw new BankSysException("Limit for suspicious wasn't defined");
                }

                if (IsSus(clientId))
                {
                    res= (operation != OperationTYPE.CASH_OUT && operation != OperationTYPE.TRANSFER) ||
                           (!(amount > _susLimits));
                }
                else
                {
                    res = true;
                }

                if (!res)
                {
                    throw new BankSysException("Operation can't be made");
                }
            }

            public void EnsureClient(ClientId clientId)
            {
                if (!_guardedBank._clients.ContainsKey(clientId))
                {
                    throw new BankSysException("No such client");
                }
            }

            public void UniqEnsureClient(ClientId clientId)
            {
                if (_guardedBank._clients.ContainsKey(clientId))
                {
                    throw new BankSysException("Client already exists");
                }
            }

            public void EnsureAccount(ClientId clientId, AccountId accountId)
            {
                if (!(_guardedBank._accounts.ContainsKey(accountId)
                     && _guardedBank._dependencies.ContainsKey(clientId)
                     && _guardedBank._dependencies[clientId].Contains(accountId)))
                {
                    throw new BankSysException("No such account in da bank");
                }
            }

            public void EnsureTransaction(TransactionId transaction)
            {
                if (!_guardedBank._transactions.ContainsKey(transaction))
                {
                    throw new BankSysException("No such transaction in da bank");
                }
            }
            
            private bool IsSus(ClientId clientId)
            {
                var client = _guardedBank._clients[clientId];
                return client._address==null || client._id_card==null;
            }
            
        
        }
    }
}