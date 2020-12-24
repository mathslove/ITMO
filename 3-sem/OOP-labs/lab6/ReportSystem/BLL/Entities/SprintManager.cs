using System;
using System.Collections.Generic;
using System.Linq;
using lab6.ReportSystem.DAL.Entities;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.BLL.Entities
{
    public class SprintManager
    {
        private SprintsRepository _sprints;

        public SprintManager()
        {
            _sprints=new SprintsRepository();
        }

        public Sprint FindById(Guid sprintId)
        {
            return _sprints.FindById(sprintId);
        }

        public IEnumerable<Sprint> GetAll()
        {
            return _sprints.GetAll();
        }

        public Sprint GetLast()
        {
            return _sprints.GetAll().Last();
        }

        public Guid MakeSprint()
        {
            var s =new Sprint();
            _sprints.Add(s);
            return s.Id;
        }
        
        public DayReport MakeDayReport(Guid sprintId,User user, string description)
        {
            var sprint = FindById(sprintId);
            var tasks = sprint.Tasks.FindByLastUpdate(DateTime.Now.Date).Where(task => task.Assignee==user);
            var d = new DayReport(user, tasks, description);
            sprint.GetReport().AddDayReport(d);
            return d;
        }

        public SprintReport FinishSprint(Guid sprintId)
        {
            var sprint = FindById(sprintId);
            return sprint.GetReport(true);
        }
        
    }
}