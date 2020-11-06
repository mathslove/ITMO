using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.AirTransport
{
    public class Stupa: IAirTransport
    {
        public Stupa(string name)
            :base(8)
        {
            Name = name;
            Model = "Ступа";
            Series = GetHashCode().ToString();
        }
        
        public override string GetName()
        {
            return Name;
        }
        

        protected override double GetReducedDist(double distance)
        {
            return distance * 0.94;
        }
    }
}