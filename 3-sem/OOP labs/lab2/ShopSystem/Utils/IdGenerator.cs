using System.Drawing;
using lab2.ShopSystem.Exceptions;

namespace lab2.ShopSystem.Utils
{
    public class IdGenerator
    {
        private uint seed;

        public IdGenerator()
        {
            seed = 0;
        }

        public uint GenerateUniqId()
        {
            if (seed == uint.MaxValue)
                throw new ShopSysException("Cannot generate more uniq IDs");

            return ++seed;
        }
        
    }
}