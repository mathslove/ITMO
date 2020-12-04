using System;
using System.Collections.Generic;
using lab5.BankSystem.Entites;
using lab5.BankSystem.Exception;

namespace lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            // Задаём политику банка, по кредитам и приколам
            var debp = new DebitPolicyFixed();
            debp.SetInterest(3);
            var depp = new DepositPolicyThreeWay();
            depp.SetBounds(50000, 100000);
            depp.SetInterests(3,4,5);
            var crep = new CreditPolicyFixed();
            crep.SetCommission(8);
            var policy = new BankPolicy(debp,depp,crep);
            policy.SetLimitForSus(5000);
            
            //Создаём банки
            var tinkoff = new Bank("Олег",policy);
            var putin = new Bank("Стабильность", policy);
            
            //Делаем клиента
            var dotter = new Client("Роман", "Макаревич");// создаём подозрительного клиента
            var C1=tinkoff.AddClient(dotter);
            var C2 = putin.AddClient(dotter);
            
            var b1a1 = tinkoff.CreateDebitAccount(C1);
            var b1a2 = tinkoff.CreateCreditAccount(C1, 1000);
            var b1a3 = tinkoff.CreateDepositAccount(C1, 100, 100);
                
            var b2a1 = putin.CreateDebitAccount(C1);
            var b2a2 = putin.CreateCreditAccount(C1, 1000);
            var b2a3 = putin.CreateDepositAccount(C1, 100, 100);
            
            //Производим операции
            try
            {
                
                //Пополняем
                var t1 = tinkoff.CashIn(C1, b1a1, 100);
                //Снимаем
                var t2 = putin.CashOut(C2, b2a2, 100);
                //Переводим в другой банк
                var t3 = tinkoff.Transfer(100,C1, b1a2, C2, b1a1, putin);
                //Отменим перевод
                tinkoff.CancelOperation(t3);
                
            }
            catch (BankSysException e)
            {
                Console.WriteLine(e);
            }
            

        }
    }
}