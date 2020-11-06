using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.LandTransport
{
    public class BactrianCamel: ILandTransport
    {
        class RestDurationTime
        {
            private bool IsFirst = true;
            private readonly double first = 5;
            private readonly double common = 8;

            public double GetTime()
            {
                if (!IsFirst) return common;
                IsFirst = !IsFirst;
                return first;
            }

            public void Reset()
            {
                IsFirst = true;
            }
        }

        private RestDurationTime RD_Handler;
        
        public BactrianCamel(string name)
            : base(10,30)
        {
            Name = name;
            Model = "Двугорбый верблюд";
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