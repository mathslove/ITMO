using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.RaceTypes
{
    class LandRace : IRaceType
    {
        public bool Verify(ITransport transport)
        {
            return transport.GetType().IsSubclassOf(typeof(ILandTransport));
        }
    }
}