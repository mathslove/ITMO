using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.LandTransport
{
    public class Centaur: ILandTransport
    {
        class RestDurationTime
        {
            private readonly double common = 2;

            public double GetTime()
            {
                return common;
            }
            public void Reset()
            {
                
            }
        }

        private RestDurationTime RD_Handler;
        
        public Centaur(string name) : base(15, 8)
        {
            Name = name;
            Model = "Кентавр";
            Series = GetHashCode().ToString();

            RD_Handler = new RestDurationTime();
        }

        public override string GetName()
        {
            return Name;
        }

        protected override double GetRestDuration()
        {
            return RD_Handler.GetTime();
        }

        protected override void ResetVehicle()
        {
            RD_Handler.Reset();
        }
    }
}