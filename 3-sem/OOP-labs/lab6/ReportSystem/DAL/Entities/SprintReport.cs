using System;
using System.Collections.Generic;

namespace lab6.ReportSystem.DAL.Entities
{
    public class SprintReport
    {
        public DateTime CreationDate { get; }
        public string Description { get; private set; }
        public List<Task> Tasks {get;}
        public List<DayReport> DayReports { get; }

        public SprintReport()
        {
            CreationDate = DateTime.Now;
            Tasks=new List<Task>();
            DayReports = new List<DayReport>();
        }

        public void EditDescription(string text)
        {
            Description = text;
        }

        public void AddDayReport(DayReport dayReport)
        {
            DayReports.Add(dayReport);
        }

        public void AddTask(Task task)
        {
            Tasks.Add(task);
        }

        public void DeleteTask(Task task)
        {
            Tasks.Remove(task);
        }
    }
}