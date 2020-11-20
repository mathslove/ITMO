using System.IO;

namespace lab4.BackupSystem.Models
{
    public class FileModel
    {
        public string Path { get; }
        public long Size { get; }

        public FileModel(string p)
        {
            Path = p;
            Size = new FileInfo(p).Length;
        }
    }
}