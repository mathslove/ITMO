using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.RaceTypes
{
    class MixedRace : IRaceType
    {
        public bool Verify(ITransport transport)
        {
            /*return transport.GetType().IsSubclassOf(typeof(IAirTransport)) || transport.GetType().IsSubclassOf(typeof(ILandTransport));*/
            return true;
        }
    }
}