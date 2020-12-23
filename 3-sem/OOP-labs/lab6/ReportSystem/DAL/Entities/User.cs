using System;

namespace lab6.ReportSystem.DAL.Entities
{
    
    public class User
    {
        private Guid Id { get; }
        public string Name { get; }
        public User Parent { get; private set; }

        public User(string name, User parent=null)
        {
            Id = Guid.NewGuid();
            Name = name;
            Parent = parent;
        }

        public void ChangeLeader(User user)
        {
            Parent = user;
        }
    }
}