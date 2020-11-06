namespace lab3.RaceSystem.Interface
{
    public abstract class IAirTransport: ITransport
    {
        protected double Speed;

        public IAirTransport(double speed)
        {
            Speed = speed;
        }
        protected abstract double GetReducedDist(double distance);

        public override bool TryCalcTime(double dist, out double res_time)
        {
            if (dist <= 0)
            {
                res_time = -1;
                return false;
            }

            res_time = GetReducedDist(dist) / Speed;
            return true;
        }
    }
}