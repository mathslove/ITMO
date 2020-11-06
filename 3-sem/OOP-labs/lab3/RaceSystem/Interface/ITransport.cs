namespace lab3.RaceSystem.Interface
{
    public abstract class ITransport
    {
        protected string Name;
        protected string Model;
        protected string Series;
        
        
        public abstract string GetName();
        public abstract bool TryCalcTime(double dist, out double res_time);
    }
}