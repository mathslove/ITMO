using System;
using lab6.ReportSystem.BLL.Entities;

namespace lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            //TODO:  помыть посуду
            // Создаём объект
            var jira = new ReportService();
            
            // Создаём пользователей
            var myId = jira.UserManager.MakeUser("Михаил");
            var me = jira.UserManager.FindById(myId);
            var peshkaId = jira.UserManager.MakeUser("Путин", me);
            
            // Создаём очень важное задание
            var tId = jira.TasksManager.MakeTask("Помыть посуду", me);
            var task = jira.TasksManager.FindById(tId);

            // Создаём спринт на мытьё посуду
            var sId = jira.SprintManager.MakeSprint();
            var sprint = jira.SprintManager.FindById(sId);
            sprint.EditDescription("Собрался наконец-то помыть посуду");
            
            // Добавляем задание в спринт
            sprint.AddTask(task);
            sprint.EditDescription("Очень важный спринт");
            
            // Делаем дела и пишем отчёт
            task.Active();
            task.EditDescription("Надоело мыть посуду");
            task.Resolve();
            jira.SprintManager.MakeDayReport(sId, me, "Помыл посуду");

            // Пишем отчёт за спринт
            var report = jira.SprintManager.FinishSprint(sId);
            
            //breakpoint
        }
    }
}