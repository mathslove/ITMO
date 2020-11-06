using System;
using System.Collections.Generic;
using lab3.RaceSystem.Entities.RaceTypes;
using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities
{
    public class Race
    {
        private string Name;
        private List<ITransport> Garage;
        
        private IRaceType Mode;

        public Race(string name)
        {
            Name = name;
            Garage = new List<ITransport>();
            Mode = new Undef();
        }

        public void SetRaceMode_Land()
        {
            Mode = new LandRace();
        }
        
        public void SetRaceMode_Air()
        {
            Mode = new AirRace();
        }
        
        public void SetRaceMode_Mixed()
        {
            Mode = new MixedRace();
        }

        public string GetName()
        {
            return Name;
        }
        
        public bool TryAdd(ITransport transport)
        {
            if (!Mode.Verify(transport))
                return false;

            foreach (var vehicle in Garage)
            {
                if (transport.Equals(vehicle))
                    return false;
            }
            
            Garage.Add(transport);
            
            return true;
        }

        public bool TryDefineWinnerOnDist(double distance, out List<ITransport> winners)
        {
            if (Garage.Count == 0)
            {
                winners =  null;
                return false;
            }

            double min = Double.MaxValue;
            winners = new List<ITransport>();
            
            foreach (var transport in Garage)
            {
                double cur;
                if (!transport.TryCalcTime(distance, out cur))
                {
                    winners = null;
                    return false;
                }

                if (min > cur)
                {
                    min = cur;
                    winners.Clear();
                    winners.Add(transport);
                }else if (min == cur)
                {
                    winners.Add(transport);
                }
            }

            return true;
        }

    }
}