using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.Transport.AirTransport
{
    public class MagicCarpet: IAirTransport
    {

        public MagicCarpet(string name)
            :base(10)
        {
            Name = name;
            Model = "Ковёр самолёт";
            Series = GetHashCode().ToString();

        }
        
        public override string GetName()
        {
            return Name;
        }
        

        protected override double GetReducedDist(double distance)
        {
            if (distance<1000)
            {
                return distance;
            }else if (distance < 5000)
            {
                return distance * 0.97;
            }else if (distance < 10000)
            {
                return distance * 0.9;
            }
            else
            {
                return distance * 0.95;
            }
        }
    }
}