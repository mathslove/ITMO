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

            public bool VerifyOperation(ClientId clientId, OperationTYPE operation, double amount)
            {
                if (double.IsNaN(_susLimits))
                {
                    throw new BankSysException("Limit for suspicious wasn't defined");
                }

                if (IsSus(clientId))
                {
                    return (operation != OperationTYPE.CASH_OUT && operation != OperationTYPE.TRANSFER) ||
                           (!(amount > _susLimits));
                }

                return true;
            }

            public bool VerifyClient(ClientId clientId)
            {
                return _guardedBank._clients.ContainsKey(clientId);
            }
            
            public bool VerifyAccount(ClientId clientId, AccountId accountId)
            {
                return _guardedBank._accounts.ContainsKey(accountId)
                       && _guardedBank._dependencies.ContainsKey(clientId)
                       && _guardedBank._dependencies[clientId].Contains(accountId);
            }

            public bool VerifyTransaction(TransactionId transaction)
            {
                return _guardedBank._transactions.ContainsKey(transaction);
            }
            
            private bool IsSus(ClientId clientId)
            {
                var client = _guardedBank._clients[clientId];
                return client._address==null || client._id_card==null;
            }
            
        
        }
    }
}