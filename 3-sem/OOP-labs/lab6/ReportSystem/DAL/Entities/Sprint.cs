using System;
using System.Collections.Generic;
using System.Linq;
using lab6.ReportSystem.BLL.Entities;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.DAL.Entities
{
    public class Sprint
    {
        private bool IsCompleted = false;
        public Guid Id { get; }
        public string Description { get; private set; }
        public TasksManager Tasks { get; }

        private readonly SprintReport SprintReport;

        public Sprint()
        {
            Id = Guid.NewGuid();
            SprintReport = new SprintReport();
            Tasks = new TasksManager();
        }

        public void AddTask(Task task)
        {
            Tasks.AddTask(task);
            SprintReport.AddTask(task);
        }

        public void DeleteTask(Guid taskId)
        {
            Tasks.DeleteTask(taskId);
            SprintReport.DeleteTask(Tasks.FindById(taskId));

        }

        public void EditDescription(string text)
        {
            Description = text;
        }

        public SprintReport GetReport(bool finish=false)
        {
            if (IsCompleted)
            {
                throw new ReportSystemException("Report is already finished!");
            }

            IsCompleted = finish;
            return SprintReport;
        }
        
    }
}