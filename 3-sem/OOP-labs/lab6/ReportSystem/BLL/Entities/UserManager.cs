using System;
using System.Collections.Generic;
using System.Configuration;
using lab6.ReportSystem.DAL.Entities;

namespace lab6.ReportSystem.BLL.Entities
{
    public class UserManager
    {
        private UsersRepository _users;

        public UserManager()
        {
            _users = new UsersRepository();
        }
        
        public User FindById(Guid id)
        {
            return _users.FindById(id);
        }

        public List<User> GetChildren(User user)
        {
            var res = new List<User>();
            foreach (var user1 in _users.GetAll())
            {
                if (user1.Parent == user)
                {
                    res.Add(user1);
                }
            }

            return res;
        }

        public Guid MakeUser(string name, User parent=null)
        {
            var u = new User(name, parent);
            _users.Add(u);
            return u.Id;
        }
        
    }
}