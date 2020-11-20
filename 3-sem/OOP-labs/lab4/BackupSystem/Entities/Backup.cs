using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using lab4.BackupSystem.Entities.AlgorithmsOfStorage;
using lab4.BackupSystem.Entities.FilterAlgo;
using lab4.BackupSystem.Models;

namespace lab4.BackupSystem.Entities
{
    public class Backup
    {
        public int Id { get; }
        DateTime CreationTime;
        private int BackupSze;
        private List<RestorePoint> Points;
        
        private List<string> Files;
        private StorageAlgo _storageAlgo;
        private List<IFilterAlgo> Filters;
        
        public Backup()
        {
            Id = GetHashCode();
            CreationTime = DateTime.Now;
            Points = new List<RestorePoint>();
            _storageAlgo = new GeneralStorageAlgo();
            Files = new List<string>();
            Filters = new List<IFilterAlgo>();
        }
        
        public void AddFilePath(string filepath)
        {
            if (!File.Exists(filepath))
            {
                throw new Exception($"Нет такого файла {filepath}\n");
            }
            
            Files.Add(filepath);
        }

        public string[] GetFilesPaths()
        {
            
            return Files.ToArray();
        }

        public bool DeleteFilePathByIndex(int i)
        {
            if (0>i || i>=Files.Count)
            {
                return false;
            }
            Files.RemoveAt(i);
            return true;
        }

        public void SetStorageAlgo(StorageAlgo algo)
        {
            _storageAlgo = algo;
        }

        public void AddFilter(IFilterAlgo filter)
        {
            Filters.Add(filter);
        }

        public void Update()
        {
            foreach (var filter in Filters)
            {
                Points = filter.Filter(this, Points);
            }
        }
        
        public RestorePointInfo CreateRestorePoint()
        {
            RestorePoint Rpoint;
            if (_storageAlgo.IsIncremental())
            {
                var NewFiles = new List<string>();
                var PossibleParent = Points[Points.Count - 1];
                foreach (var file in Files)
                {
                    long prevSize;
                    var newSize = new FileInfo(file).Length;
                    if (PossibleParent.CheckSizeOf(file, out prevSize))
                    {
                        if (Math.Abs(prevSize-newSize) != 0)
                        {
                            NewFiles.Add(file);
                        }
                    }
                    else
                    {
                        NewFiles.Add(file);
                    }
                }
                Rpoint = new RestorePoint(NewFiles.ToArray(), _storageAlgo, PossibleParent);
            }
            else
            {
                Rpoint = new RestorePoint(Files.ToArray(), _storageAlgo);
            }
            Points.Add(Rpoint);
            return Rpoint.GetInfo();
        }
        
        
        public bool DeleteRestorePointByIndex(int i)
        {
            if (i < 0 || i >= Files.Count)
                return false;

            int childIndex = -1;
            for (int j = 0; j < Points.Count; j++)
            {
                if (Points[j].HasParent(Points[i]))
                {
                    childIndex = j;
                    break;
                }
            }

            if (childIndex != -1)
            {
                var childFiles = Points[childIndex].GetInfo().FilePaths;
                var algo = _storageAlgo;
                algo.SetFullSave();
                Points[childIndex] = new RestorePoint(Points[childIndex], childFiles, algo);
            }

            Points.RemoveAt(i);
            
            
            return true;
        }
        
    }
}