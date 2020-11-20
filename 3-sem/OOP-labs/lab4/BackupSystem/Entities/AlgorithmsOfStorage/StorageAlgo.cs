namespace lab4.BackupSystem.Entities.AlgorithmsOfStorage
{
    public interface StorageAlgo
    {
        public void SetIncrementalSave();
        public void SetFullSave();
        public bool IsIncremental();
        public string GetName();
        public void StoreFiles(string[] files);
    }
}