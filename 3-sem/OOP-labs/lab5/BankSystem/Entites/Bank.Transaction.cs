namespace lab5.BankSystem.Entites
{
    using ClientId = System.Guid;
    using AccountId = System.Guid;
    using TransactionId = System.Guid;

    public partial class Bank
    {
        public class Transaction
        {
            public OperationTYPE Operation { get; }
            public double Amount { get; }
            public ClientId Client { get; }
            public AccountId Account { get; }
            public ClientId Client2 { get; }
            public AccountId Account2 { get; }
            public TransactionId Id { get; } 
            
            public Transaction(Bank.OperationTYPE operation, ClientId client, AccountId account, double amount)
            {
                Id = ClientId.NewGuid();
                
                this.Client = client;
                this.Account = account;
                this.Operation = operation;
                this.Amount = amount;
            }
            
            public Transaction(Bank.OperationTYPE operation, ClientId client1, AccountId account1,ClientId client2, AccountId account2, double amount)
            {
                Id = ClientId.NewGuid();
                
                this.Client = client1;
                this.Account = account1;
                this.Client2 = client2;
                this.Account2 = account2;
                
                this.Operation = operation;
                this.Amount = amount;

            }
        }
    }
}