using System.Collections.Generic;

namespace lab4.BackupSystem.Entities.FilterAlgo
{
    public enum FilterInteraction
    {
        AND,
        OR
    }
    
    public interface IFilterAlgo
    {
        public int Filter(Backup backup, List<RestorePoint> points);
    }
}