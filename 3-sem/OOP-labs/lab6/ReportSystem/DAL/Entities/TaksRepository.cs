using System;
using System.Collections.Generic;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.DAL.Entities
{
    public class TaksRepository
    {
        private List<Task> _tasks = new List<Task>();

        public Task find_by_id(Guid id)
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

        public List<Task> find_by_creation_date(DateTime time)
        {
            var res = new List<Task>();
            foreach (var task in _tasks)
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

        public List<Task>  FindByLastUpdate(DateTime time)
        {
            var res = new List<Task>();
            foreach (var task in _tasks)
            {
                if (time == task.UpdateTime)
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

        public List<Task> FindByUser(User user)
        {
            var res = new List<Task>();
            foreach (var task in _tasks)
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
        
        public List<Task> FindByUpd(User usr)
        {
            var res = new List<Task>();
            foreach (var task in _tasks)
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

        public Task MakeTask(string name, User parent = null)
        {
            var task = new Task(name, parent);
            _tasks.Add(task);
            return task;
        }
        
    }
}