using System;
using System.Collections.Generic;
using System.IO;
using lab4.BackupSystem.Entities.AlgorithmsOfStorage;
using lab4.BackupSystem.Models;

namespace lab4.BackupSystem.Entities
{
    public class RestorePoint
    {
        private List<FileModel> Files = 
            new List<FileModel>();
        private StorageAlgo _storageAlgo;
        private long Size;
        private DateTime CreationTime;
        private RestorePoint Parent;
        
        public RestorePoint(string[] Files, StorageAlgo storageAlgo, RestorePoint from=null)
        {
            CreationTime = DateTime.Now;
            FormateFiles(Files);
            _storageAlgo = storageAlgo;
            Parent = from;
            CalcSize();
            StoreFiles();
        }

        public RestorePoint(RestorePoint point, string[] Files,  StorageAlgo storageAlgo,RestorePoint from=null)
        {
            this.CreationTime = point.CreationTime;
            FormateFiles(Files);
            _storageAlgo = storageAlgo;
            Parent = from;
            CalcSize();
        }
        
        public long GetSize()
        {
            return Size;
        }

        /*public long GetFullSize()
        {
            long res = 0;
            if (Parent!=null)
            {
                res += Parent.GetSize();
            }

            res += GetSize();
            
            return res;
        }*/
        
        public DateTime GetCreationTime()
        {
            return CreationTime;
        }

        public bool HasParent(RestorePoint point)
        {
            return Parent == point;
        }

        public bool CheckSizeOf(string path, out long size)
        {
            foreach (var file in Files)
            {
                if (file.Path == path)
                {
                    size = file.Size;
                    return true;
                }
            }

            if (Parent!=null)
            {
                return CheckSizeOf(path, out size);
            }

            size = 0;
            return false;
        }

        public RestorePointInfo GetInfo()
        {
            var Paths = new List<string>();
            foreach (var file in Files)
            {
                Paths.Add(file.Path);
            }
            
            /*if (Parent!=null)
            {
                Paths.AddRange(Parent.GetInfo().FilePaths);
            }*/
            
            return new RestorePointInfo(Paths.ToArray(), GetSize(), _storageAlgo, GetCreationTime());
        }

        private void FormateFiles(string[] NewFiles)
        {
            foreach (var file in NewFiles)
            {
                this.Files.Add(new FileModel(file));
            }
        }
        
        private void CalcSize()
        {
            long result = 0;
            foreach (var file in Files)
            {
                result += file.Size;
            }

            Size = result;
        }
        
        private void StoreFiles()
        {
            List<string> Paths = new List<string>();
            foreach (var file in Files)
            {
                Paths.Add(file.Path);
            }
            _storageAlgo.StoreFiles(Paths.ToArray());
        }
    }
}