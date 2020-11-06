using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.RaceTypes
{
    class Undef : IRaceType
    {
        public bool Verify(ITransport transport)
        {
            return false;
        }
    }
}