using System;
using lab4.BackupSystem.Entities.AlgorithmsOfStorage;

namespace lab4.BackupSystem.Entities
{
    public class RestorePointInfo
    {
        public string[] FilePaths { get; }
        public long Size { get; }
        public DateTime CreationTime { get; }
        public StorageAlgo Algo;
        
        public RestorePointInfo(string[] filePaths, long size,StorageAlgo storageAlgo, DateTime creationTime)
        {
            FilePaths = filePaths;
            Size = size;
            CreationTime = creationTime;
            Algo = storageAlgo;
        }

        public string GetAllInfoByString()
        {
            string msg = $"Restore Point was created on {CreationTime:G}\n" +
                         $"Has the size of {Size}\n" +
                         $"And use {Algo.GetName()}\n" +
                         $"Store this files:\n {String.Join("\n", FilePaths)}";
            return msg;
        }
    }
}