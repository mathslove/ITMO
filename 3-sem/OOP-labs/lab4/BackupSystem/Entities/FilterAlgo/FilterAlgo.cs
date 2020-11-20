using System.Collections.Generic;

namespace lab4.BackupSystem.Entities.FilterAlgo
{
    public interface IFilterAlgo
    {
        public List<RestorePoint> Filter(Backup backup, List<RestorePoint> points);
    }
}