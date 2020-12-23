namespace lab6.ReportSystem.Exceptions
{
    public class ReportSystemException: System.Exception
    {
        private const string DefaultM = "Report System has failed! \n";

        public ReportSystemException(string m) :
            base(DefaultM + m + "\n")
        {
        }
    }
}