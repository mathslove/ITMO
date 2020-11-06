using System;
using System.IO;
using lab1.Parser;
using lab1.Parser.Exceptions;


namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = @"test.ini";
            
            
            var ini = new IniParser();

            try
            {
                ini.Parse(path);
            }
            catch (IniParserException e)
            {
                Console.Write(e.Message);
            }
            catch (IOException e)
            {
                Console.Write(e.Message);
            }
            catch (Exception e)
            {
                Console.Write(e.Message);
            }
            
            
            Console.WriteLine("Введите через пробел тип, название секции и переменную");
            var s = string.Empty;
            while ((s = Console.ReadLine().Trim()) != "q")
            {
                var cmd = s.Split(" ");
                try
                {
                    if (cmd[0] == "int")
                    {
                        Console.WriteLine(ini.TryGet<int>(cmd[1], cmd[2]));
                    }
                    else if (cmd[0] == "float")
                    {
                        Console.WriteLine(ini.TryGet<float>(cmd[1], cmd[2]));
                    }

                    if (cmd[0] == "string")
                    {
                        Console.WriteLine(ini.TryGet<string>(cmd[1], cmd[2]));
                    }
                }
                catch (Exception e)
                {
                    Console.Write(e.Message);
                }
            }
            
        }
    }
}