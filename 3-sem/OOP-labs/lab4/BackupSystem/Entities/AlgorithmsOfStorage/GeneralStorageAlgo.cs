namespace lab4.BackupSystem.Entities.AlgorithmsOfStorage
{
    public class GeneralStorageAlgo: StorageAlgo
    {
        private bool _isIncremental = false;
        private const string Name = "General algorithm of stroage";
        public void SetIncrementalSave()
        {
            _isIncremental = true;
        }

        public void SetFullSave()
        {
            _isIncremental = false;
        }

        public bool IsIncremental()
        {
            return _isIncremental;
        }
        
        public string GetName()
        {
            string additional;
            if (_isIncremental)
            {
                additional = "with incremental method of storage";
            }
            else
            {
                additional = "with general method of storage";
            }
            return Name+additional;
        }

        public void StoreFiles(string[] files)
        {
            ;
        }
    }
}