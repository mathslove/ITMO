using System.Collections.Generic;

namespace lab4.BackupSystem.Entities.FilterAlgo
{
    public class SizeFilter:IFilterAlgo
    {
        protected int SizeLimit;
        public SizeFilter(int sizeLimit)
        {
            SizeLimit = sizeLimit;
        }
        public List<RestorePoint> Filter(Backup backup, List<RestorePoint> points)
        {
            for (int i = 0; i < points.Count; i++)
            {
                if (points[i].GetSize()<SizeLimit)
                {
                    backup.DeleteRestorePointByIndex(i);
                }
            }

            return points;
        }
    }
}