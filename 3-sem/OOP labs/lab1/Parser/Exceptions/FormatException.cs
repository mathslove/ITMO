namespace lab1.Parser.Exceptions
{
    public class IniParserFormatException : IniParserException
    {
        private const string DefaultM = "IniParser has failed reading file due to wrong format. \n";

        public IniParserFormatException():
            base(DefaultM){}
        public IniParserFormatException(string what) :
            base(DefaultM + what + "\n"){}
    }
}