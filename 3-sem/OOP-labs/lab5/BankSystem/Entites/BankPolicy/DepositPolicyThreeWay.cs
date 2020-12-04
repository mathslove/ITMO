using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    public class DepositPolicyThreeWay: IDepositPolicy
    {
        private double _lower_bound;
        private double _upper_bound;
        private double _1level_interest;
        private double _2level_interest;
        private double _3level_interest;

        public uint period { get; private set; }
        public void SetInterests(double first_interest, double second_interest, double third_interest)
        {
            _1level_interest = first_interest;
            _2level_interest = second_interest;
            _3level_interest = third_interest;
        }
        
        public void SetBounds(double lower_bound, double upper_bound)
        {
            _lower_bound = lower_bound;
            _upper_bound = upper_bound;
        }
        

        public double GetInterestOnBalance(double balance)
        {
            if (balance < _lower_bound)
            {
                return _1level_interest;
            }
            else if (balance > _upper_bound)
            {
                return _3level_interest;
            }
            else
            {
                return _2level_interest;
            }
        }
    }
}