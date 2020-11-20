using System.Collections.Generic;

namespace lab4.BackupSystem.Entities.FilterAlgo
{
    public class CountFilter:IFilterAlgo
    {
        private int countLimit;
        public CountFilter(int c)
        {
            countLimit = c;
        }

        public int Filter(Backup backup, List<RestorePoint> points)
        {
            return points.Count - countLimit;
        }
    }
}