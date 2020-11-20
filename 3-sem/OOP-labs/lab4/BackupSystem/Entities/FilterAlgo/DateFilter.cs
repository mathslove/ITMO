using System;
using System.Collections.Generic;
using System.Drawing;

namespace lab4.BackupSystem.Entities.FilterAlgo
{
    public class DateFilter:IFilterAlgo
    {
        private DateTime FilterDate;
        public DateFilter(DateTime date)
        {
            FilterDate = date;
        }
        
        public List<RestorePoint> Filter(Backup backup,List<RestorePoint> points)
        {
            for (int i = 0; i < points.Count; i++)
            {
                if (points[i].GetCreationTime()< FilterDate)
                {
                    backup.DeleteRestorePointByIndex(i);
                }
            }

            return points;
        }
    }
}