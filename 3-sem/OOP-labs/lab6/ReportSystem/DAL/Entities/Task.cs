using System;
using System.Collections.Generic;
using lab6.ReportSystem.DAL.Entities.TaskState;
using lab6.ReportSystem.DAL.Interfaces;

namespace lab6.ReportSystem.DAL.Entities
{
    public struct Task
    {
        public Guid Id { get; }
        public string Name { get; }
        public string Description { get; private set; }
        public List<string> Comments { get; private set; }
        public ITaskState State { get; private set; }
        public DateTime CreationTime { get; }
        public DateTime UpdateTime { get; private set; }
        public User Assignee { get; private set;  }

        public Task(string name, User user=null)
        {
            Id = Guid.NewGuid();
            Name = name;
            State = new OpenState();
            CreationTime = DateTime.Now;
            UpdateTime = DateTime.Now;
            Assignee = user;
            Comments = new List<string>();
            Description = String.Empty;
        }

        public void Active()
        {
            State= new ActiveState();
            UpdateTime = DateTime.Now;
        }

        public void Resolve()
        {
            State = new ResolvedState();
            UpdateTime = DateTime.Now;
        }

        public void AssignUser(User user)
        {
            Assignee = user;
            UpdateTime = DateTime.Now;
        }

        public void EditDescription(string description)
        {
            Description = description;
            UpdateTime = DateTime.Now;
        }

        private void AddComment(string comment)
        {
            Comments.Add(comment);
            UpdateTime=DateTime.Now;
        }
        
    }
}