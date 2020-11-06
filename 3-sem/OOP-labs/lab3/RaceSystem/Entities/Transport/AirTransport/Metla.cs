using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.AirTransport
{
    public class Metla: IAirTransport
    {
        public Metla(string name)
            :base(20)
        {
            Name = name;
            Model = "Метла";
            Series = GetHashCode().ToString();

        }
        
        public override string GetName()
        {
            return Name;
        }
        

        protected override double GetReducedDist(double distance)
        {
            return distance * (1 - (int) distance / 1000 / 100);
        }
    }
}