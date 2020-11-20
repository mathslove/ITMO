using System;
using lab4.BackupSystem.Entities;
using lab4.BackupSystem.Entities.FilterAlgo;

namespace lab4
{
    class Program
    {
        static void Main(string[] args)
        {
            ////////////// Кейс №1
            //Создали Бэкап
            var backup1 = new Backup();
            
            //Добавили два файла
            try
            {
                backup1.AddFilePath(@"C:\Users\mmas6\OneDrive\Документы\temp\1.txt");
                backup1.AddFilePath(@"C:\Users\mmas6\OneDrive\Документы\temp\2.txt");
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            //Ctrl-S
            var info = backup1.CreateRestorePoint().GetAllInfoByString();
            Console.WriteLine(info);
            Console.WriteLine("------------------");
            
            //Ctrl-S
            info = backup1.CreateRestorePoint().GetAllInfoByString();
            Console.WriteLine(info);
            Console.WriteLine("------------------");
            
            //Добавляем фльтр 
            backup1.AddFilter(new CountFilter(1));
            
            // Проерить сколько осталось можно через дебаг или сделать getter для points
            // Console.WriteLine(backup1.Points.Count);
            
            
            ////////////// Кейс №2
            // Ёмаё где взять файлы по 100м 
            // Сделаю сорт до 1к байт
            var backup2 = new Backup();
            
            // добавляем
            try
            {
                backup2.AddFilePath(@"C:\Users\mmas6\OneDrive\Документы\temp\MyBigFatPUDGE.txt");
                backup2.AddFilePath(@"C:\Users\mmas6\OneDrive\Документы\temp\MyLittleSlimShady.txt");
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            //Создаём 
            info = backup2.CreateRestorePoint().GetAllInfoByString();
            Console.WriteLine(info);
            Console.WriteLine("------------------");
            
            // новый фильтр
            backup2.AddFilter(new SizeFilter(1000));
            
            // ФИльТруЕМ
            backup2.Update();
            // Console.WriteLine(backup2.Points.Count);
            
            // Кейс на инкремент
            // Воьзьму просто первый кейс и докину ещё файлик
            try
            {
                backup1.AddFilePath(@"C:\Users\mmas6\OneDrive\Документы\temp\MyBigFatPUDGE.txt");
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
            info = backup1.CreateRestorePoint().GetAllInfoByString();
            Console.WriteLine(info);
            Console.WriteLine("------------------");
            
            // Кейс на два фильтра ко второму
            // Создам ещё одну точку, но из другого файла
            backup2.DeleteFilePathByIndex(0);
            backup2.DeleteFilePathByIndex(1);
            info = backup2.CreateRestorePoint().GetAllInfoByString();
            Console.WriteLine(info);
            
            // новый фильтр
            backup2.AddFilter(new CountFilter(1));
            
            // ФИльТруЕМ
            backup2.Update();
            // Console.WriteLine(backup2.Points.Count);
        }
    }
}