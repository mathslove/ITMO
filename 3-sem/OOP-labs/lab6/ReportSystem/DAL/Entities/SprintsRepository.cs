using System;
using System.Collections.Generic;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.DAL.Entities
{
    public class SprintsRepository
    {
        private List<Sprint> _sprints;

        public SprintsRepository()
        {
            _sprints=new List<Sprint>();
        }
        
        public Sprint FindById(Guid id)
        {
            foreach (var sprint in _sprints)
            {
                if (sprint.Id == id)
                {
                    return sprint;
                }
            }
            throw new ReportSystemException($"No sprint was found with such id {id} !");
        }

        public IEnumerable<Sprint> GetAll()
        {
            return _sprints;
        }

        public void Add(Sprint sprint)
        {
            _sprints.Add(sprint);
        }

        public void Delete(Guid sprintId)
        {
            if (!_sprints.Remove(FindById(sprintId)))
            {
                throw new ReportSystemException($"No such sprint with id {sprintId}!");
            }
        }
    }
}