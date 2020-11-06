namespace lab3.RaceSystem.Interface
{
    public abstract class ILandTransport: ITransport
    {
        protected double Speed;
        protected double RestInterval;

        public ILandTransport(double speed, double restInterval)
        {
            Speed = speed;
            RestInterval = restInterval;
        }
        protected abstract double GetRestDuration();
        protected abstract void ResetVehicle();
        public override bool TryCalcTime(double dist, out double res_time)
        {
            ResetVehicle();
            if (!(dist > 0))
            {
                res_time = -1;
                return false;
            }

            res_time = 0;
            while (dist > 0)
            {
                var time = dist / Speed;
                if (time >= RestInterval)
                {
                    res_time += RestInterval;
                    res_time += GetRestDuration();
                    dist -= RestInterval * Speed;
                }
                else
                {
                    res_time += time;
                    dist -= time * Speed;
                }
            }

            return true;
        }
    }
}