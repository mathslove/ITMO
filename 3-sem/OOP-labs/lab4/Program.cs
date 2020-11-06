using System;
using System.Collections.Generic;
using lab3.RaceSystem.Entities;
using lab3.RaceSystem.Entities.Transport.AirTransport;
using lab3.RaceSystem.Entities.Transport.LandTransport;
using lab3.RaceSystem.Interface;

namespace lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            var dist = 1000;
            
            // Создаём гонку
            var F1 = new Race("F1");
            // Задаём тип гонки
            F1.SetRaceMode_Land();
            
            // Создаём машинки
            ITransport[] balit = new ITransport[4];
            balit[0] = new SpeedyCamel("Быстрый верблюд");
            balit[1] = new BactrianCamel("Двугорбый верблюд");
            balit[2] = new Centaur("Кентавр");
            balit[3] = new SuperBoots("Ботинки");

            // Добавляем машинки в гоку
            foreach (var transport in balit)
            {
                if (!F1.TryAdd(transport))
                {
                    Console.WriteLine($"{transport} не получилось добавить в гонку F1");
                }
            }

            // Определяем победителя или победителей
            var winners = new List<ITransport>();
            if (!F1.TryDefineWinnerOnDist(dist, out winners))
            {
                Console.WriteLine($"{F1.GetName()} не вышло посчитать резы, вы сделали косяк, отрицательнное расстояние");
            }

            // Выоводим победителей
            Console.WriteLine($"Winners of {F1.GetName()}");
            foreach (var winner in winners)
            {
                Console.WriteLine(winner.GetName());
            }
            //------------------------------------
            //------------------------------------
            
            // Всё тоже самое, но в лётном формате
            var A1 = new Race("A1");
            A1.SetRaceMode_Air();

            ITransport[] jet = new ITransport[3];
            jet[0] = new MagicCarpet("Друг Аладина");
            jet[1] = new Stupa("Old, but gold");
            jet[2] = new Metla("Метла");

            foreach (var transport in jet)
            {
                if (!A1.TryAdd(transport))
                {
                    Console.WriteLine($"{transport} не получилось добавить в гонку {A1.GetName()}");
                }
            }
            
            if (!A1.TryDefineWinnerOnDist(dist, out winners))
            {
                Console.WriteLine($"{A1.GetName()} не вышло посчитать резы, вы сделали косяк, отрицательнное расстояние");
            }
            
            Console.WriteLine($"Winners of {A1.GetName()}");
            foreach (var winner in winners)
            {
                Console.WriteLine(winner.GetName());
            }
            //-----------------------------------
            //-----------------------------------
            
        }
    }
}