using System;
using System.Collections.Generic;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.DAL.Entities
{
    public class TasksRepository
    {
        private List<Task> _tasks;

        public TasksRepository()
        {
            _tasks=new List<Task>();
        }

        public Task FindById(Guid id)
        {
            foreach (var task in _tasks)
            {
                if (task.Id == id)
                {
                    return task;
                }
            }
            throw new ReportSystemException($"No task was found with such id {id} !");
        }

        public IEnumerable<Task> GetAll()
        {
            return _tasks;
        }

        public void Add(Task task)
        {
            _tasks.Add(task);
        }

        public void Delete(Guid taskId)
        {
            if (!_tasks.Remove(FindById(taskId)))
            {
                throw new ReportSystemException($"No such task with id {taskId}!");
            }
        }
        
    }
}