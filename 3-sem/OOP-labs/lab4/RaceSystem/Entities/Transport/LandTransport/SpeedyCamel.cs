using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.LandTransport
{
    public class SpeedyCamel:ILandTransport
    {
        class RestDurationTime
        {
            private uint count = 1;
            private readonly double first = 5;
            private readonly double second = 6.5;
            private readonly double common = 8;

            public double GetTime()
            {
                if (count == 1)
                {
                    count++;
                    return first;
                }
                if (count == 2)
                {
                    count++;
                    return second;
                }

                return common;
            }

            public void Reset()
            {
                count = 0;
            }
        }
        
        private RestDurationTime RD_Handler;
        
        public SpeedyCamel(string name) : base(40,10)
        {
            Name = name;
            Model = "Скоростной верблюд";
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
            
        }
    }
}