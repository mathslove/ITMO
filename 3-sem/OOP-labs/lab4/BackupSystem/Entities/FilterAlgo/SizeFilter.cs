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
        public int Filter(Backup backup, List<RestorePoint> points)
        {
            int count = 0;
            long sumS = 0;
            for (int i = points.Count-1; i >=0; i--)
            {
                sumS += points[i].GetSize();
                count++;
                if (sumS >= backup.GetSize())
                {
                    break;
                }
            }

            return points.Count - count;
        }
    }
}