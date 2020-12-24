using System;
using System.Collections.Generic;

namespace lab6.ReportSystem.DAL.Entities
{
    public class DayReport
    {
        public User Author { get; }
        public IEnumerable<Task> UpdatedTasks { get; }
        public DateTime CreationDate { get; }
        public string Description { get; }

        public DayReport(User author, IEnumerable<Task> updatedTasks, string description)
        {
            Author = author;
            UpdatedTasks = updatedTasks;
            CreationDate = DateTime.Now;
            Description = description;
        }
    }
}