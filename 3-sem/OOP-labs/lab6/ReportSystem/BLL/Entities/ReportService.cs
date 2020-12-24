using System;
using lab6.ReportSystem.DAL.Entities;

namespace lab6.ReportSystem.BLL.Entities
{
    public class ReportService
    {
        public TasksManager TasksManager { get; }
        public SprintManager SprintManager { get; }
        public UserManager UserManager { get; }

        public ReportService()
        {
            TasksManager = new TasksManager();
            SprintManager = new SprintManager();
            UserManager = new UserManager();
        }

        public DayReport MakeDayReport(Guid sprintId, User assignee, string description = null)
        {
            return SprintManager.MakeDayReport(sprintId, assignee,description);
        }

        public SprintReport MakeSprintReport(Guid sprintId)
        {
            return SprintManager.FinishSprint(sprintId);
        }
    }
}