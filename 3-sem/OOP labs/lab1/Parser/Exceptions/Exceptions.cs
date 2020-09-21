using System;

namespace lab1.Parser.Exceptions
{
    public class IniParserException : Exception
    {
        private const string DefaultM = "IniParser has failed its job. \n";
        
        public IniParserException():
            base(DefaultM){}
        public IniParserException(string what) :
            base(DefaultM + what){}
    }
}