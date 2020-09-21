using System;
using System.IO;
using lab1.Parser;
using lab1.Parser.Exceptions;

/*using lab1.Parser;*/

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

            Console.Write(ini.TryGet<float>("database", "float_field"));
        }
    }
}