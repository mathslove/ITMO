namespace lab1.Parser.Exceptions
{
    public class IniParserAccessException : IniParserException
    {
        private const string DefaultM = "IniParser can't access requested object \n";

        public IniParserAccessException():
            base(DefaultM){}
        public IniParserAccessException(string what) :
            base(DefaultM + what + "\n"){}
    }
}