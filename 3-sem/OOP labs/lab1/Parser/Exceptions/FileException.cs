namespace lab1.Parser.Exceptions
{
    public class IniParserFileException : IniParserException
    {
        private const string DefaultM = "IniParser has failed file work. \n";

        public IniParserFileException():
            base(DefaultM){}
        public IniParserFileException(string what) :
            base(DefaultM + what){}
    }
}