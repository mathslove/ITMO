using System;

namespace lab3.RaceSystem.Exceptions
{
    public class RaceSystemException: Exception
    {
        private const string DefaultM = "Race System has failed! \n";
        
        public RaceSystemException(string m):
            base(DefaultM + m + "\n"){}
    }
}