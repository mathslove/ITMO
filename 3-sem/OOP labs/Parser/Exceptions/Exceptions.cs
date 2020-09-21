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

    public class IniParserFileException : IniParserException
    {
        private const string DefaultM = "IniParser has failed file work. \n";

        public IniParserFileException():
            base(DefaultM){}
        public IniParserFileException(string what) :
            base(DefaultM + what){}
    }
    
    public class IniParserFormatException : IniParserException
    {
        private const string DefaultM = "IniParser has failed reading file due to wrong format. \n";

        public IniParserFormatException():
            base(DefaultM){}
        public IniParserFormatException(string what) :
            base(DefaultM + what + "\n"){}
    }
    
    public class IniParserAccessException : IniParserException
    {
        private const string DefaultM = "IniParser can't access requested object \n";

        public IniParserAccessException():
            base(DefaultM){}
        public IniParserAccessException(string what) :
            base(DefaultM + what + "\n"){}
    }
    
}