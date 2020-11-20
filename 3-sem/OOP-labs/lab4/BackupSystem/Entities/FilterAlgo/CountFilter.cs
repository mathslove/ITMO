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

        public List<RestorePoint> Filter(Backup backup, List<RestorePoint> points)
        {
            for (int i = 0; i < points.Count-countLimit; i++)
            {
                backup.DeleteRestorePointByIndex(i);
            }

            return points;
        }
    }
}