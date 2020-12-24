using System;
using System.Collections.Generic;
using lab6.ReportSystem.DAL.Entities;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.BLL.Entities
{
    public class TasksManager
    {
        private TasksRepository _tasks;

        public TasksManager()
        {
            _tasks = new TasksRepository();
        }
        
        public Task FindById(Guid id)
        {
            return _tasks.FindById(id);
        }
        
        public IEnumerable<Task> FindByCreationDate(DateTime time)
        {
            var res = new List<Task>();
            foreach (var task in _tasks.GetAll())
            {
                if (task.CreationTime == time)
                {
                    res.Add(task);
                }
            }

            if (res.Count == 0)
            {
                throw new ReportSystemException($"No task was found with such creation time {time} !");
            }
            return res;
        }

        public IEnumerable<Task>  FindByLastUpdate(DateTime time)
        {
            var res = new List<Task>();
            foreach (var task in _tasks.GetAll())
            {
                if (time == task.UpdateTime.Date)
                {
                    res.Add(task);
                }
            }

            if (res.Count == 0)
            {
                throw new ReportSystemException($"No task was found with such update time {time} !");
            }

            return res;
        }

        public IEnumerable<Task> FindByUser(User user)
        {
            var res = new List<Task>();
            foreach (var task in _tasks.GetAll())
            {
                if (task.Assignee == user)
                {
                    res.Add(task);
                }
            }

            if (res.Count ==0)
            {
                throw new ReportSystemException($"No task was found with such user {user.Name} !");
            }

            return res;
        }
        
        public IEnumerable<Task> FindByUpd(User usr)
        {
            var res = new List<Task>();
            foreach (var task in _tasks.GetAll())
            {
                if (task.Assignee == usr && task.CreationTime != task.UpdateTime)
                {
                    res.Add(task);
                }
            }

            if (res.Count ==0)
            {
                throw new ReportSystemException($"No task was found with such user and update {usr.Name} !");
            }

            return res;
        }

        public Guid MakeTask(string name, User parent)
        {
            var task = new Task(name, parent);
            _tasks.Add(task);
            return task.Id;
        }

        public void AddTask(Task task)
        {
            _tasks.Add(task);
        }

        public void DeleteTask(Guid taskId)
        {
            _tasks.Delete(taskId);
        }
    }
}