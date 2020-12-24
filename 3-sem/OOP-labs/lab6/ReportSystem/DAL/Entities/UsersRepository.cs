using System;
using System.Collections.Generic;
using lab6.ReportSystem.Exceptions;

namespace lab6.ReportSystem.DAL.Entities
{
    public class UsersRepository
    {
        private List<User> _users;

        public UsersRepository()
        {
            _users=new List<User>();
        }

        public User FindById(Guid userId)
        {
            foreach (var user in _users)
            {
                if (user.Id == userId)
                {
                    return user;
                }
            }
            throw new ReportSystemException($"No user was found with such id {userId} !");
        }

        public IEnumerable<User> GetAll()
        {
            return _users;
        }

        public void Add(User user)
        {
            _users.Add(user);
        }

        public void Delete(Guid userId)
        {
            _users.Remove(FindById(userId));
        }
        
    }
}