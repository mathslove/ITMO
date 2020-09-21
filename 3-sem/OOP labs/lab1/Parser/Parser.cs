using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text.RegularExpressions;
using lab1.Parser.Exceptions;

namespace lab1.Parser
{
    public class IniParser
    {
        class Data
        {
            public Dictionary<string, Dictionary<string, string>> data;

            public Data()
            {
                data = new Dictionary<string, Dictionary<string, string>>();
            }

            public void AddSection(string new_section)
            {
                if (!data.ContainsKey(new_section))
                    data.Add(new_section, new Dictionary<string, string>());
                else
                    throw new IniParserFormatException($"Section name {new_section} is already exists!");
            }

            public void AddProperties(string section, string new_param, string val)
            {
                if (data.ContainsKey(section))
                {
                    if (!data[section].ContainsKey(new_param))
                        data[section].Add(new_param, val);
                    else
                        throw new IniParserFormatException($"Parameter name {new_param} in section {section} is already exists!");
                }
                else
                {
                    throw new IniParserFormatException($"Section name {section} doesn't exists!");
                }

            }

            public string GetValue(string SectionName, string PropertyName)
            {
                if (data.ContainsKey(SectionName))
                {
                    if (data[SectionName].ContainsKey(PropertyName))
                        return data[SectionName][PropertyName];
                    else
                        throw new IniParserAccessException($"No such section {PropertyName}");

                }
                else
                {
                    throw new IniParserAccessException($"No such section {SectionName}");
                }
            }
        }

        private Data data;
        
        public IniParser()
        {
            data = new Data();
        }

        public void Parse(string path)
        {
            // Проверка файла
            if (!File.Exists(path))
                throw new IniParserFileException("No such file in give path!");
            
            using (FileStream fsi = new FileStream(path, FileMode.Open))
            {
                using (StreamReader sri = new StreamReader(fsi))
                {
                    string line;
                    string SectionName="";
                    
                    while ((line =  sri.ReadLine()) != null)
                    {
                        // Убираем комментарии из файла
                        line = RemoveComments(line);
                        if (line == string.Empty)
                            continue;

                        // Работа с секцией
                        if (IsSectionName(line))
                        {
                            SectionName = GetSectionName(line);
                            data.AddSection(SectionName);
                            continue;
                        }

                        // Работа с параметрами
                        var paramters = GetParametrs(line);
                        data.AddProperties(SectionName, paramters.Item1, paramters.Item2);
                    }
                }
            }

            
        }

        public T TryGet<T>(string SectionName, string PropertyName)
        {
            var value = data.GetValue(SectionName,PropertyName);
            try
            {
                if (typeof(T) == typeof(float) || typeof(T) == typeof(double))
                    return (T) Convert.ChangeType(value, typeof(T), CultureInfo.InvariantCulture);
                else
                    return (T) Convert.ChangeType(value, typeof(T));
            }
            catch (IniParserException e)
            {
                throw;
            }
            catch (Exception e)
            {
                throw new IniParserAccessException($"Can't convert requested value {value} to given type {typeof(T)} ");
            }
        }
        
        private string RemoveComments(string str)
        {
            str = str.Trim();
            
            var index = str.IndexOfAny(new[] {';','#'});
            if (index == -1)
                index = str.Length;
            
            str = str.Substring(0, index);
            
            return str;
        }

        private bool IsSectionName(string str)
        {
            if (str.StartsWith("[") && str.EndsWith("]"))
            {
                var SectionName = str.Substring(1, str.Length - 2);
                return Regex.IsMatch(SectionName, @"[A-Za-z0-9_]+");
            }
            else
                return false;
        }
        
        private string GetSectionName(string str)
        {
            return str.Substring(1, str.Length - 2);
        }

        private (string, string) GetParametrs(string str)
        {
            str = str.Trim();
            var index = str.IndexOfAny(new[] {'='});
            if (index == -1)
                throw new IniParserFormatException($"Invalid string given as a parameter {str} ");

            var varable = str.Substring(0, index);
            varable = varable.Trim();
            if (!Regex.IsMatch(varable, @"[A-Za-z0-9_]+"))
                throw new IniParserFormatException($"Can't use such format for names{varable}");

            var val = str.Substring(index + 1, str.Length -index - 1);
            val = val.Trim();
            
            return (varable, val);
        }
    }
}