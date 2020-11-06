using lab3.RaceSystem.Interface;

namespace lab3.RaceSystem.Entities.RaceTypes
{
    interface IRaceType
    {
        public bool Verify(ITransport transport);
    }
}