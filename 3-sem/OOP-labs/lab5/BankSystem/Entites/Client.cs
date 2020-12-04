using System;
using System.Collections.Generic;
using System.Drawing;
using lab5.BankSystem.Interfaces;

namespace lab5.BankSystem.Entites
{
    using ClientId = System.Guid;
    public class Client
    {
        // Identifier 
        private ClientId _id;
        
        // Info
        public string _name { get; private set; }
        public string _surname{ get; private set; }
        public string _address{ get; private set; }
        public string _id_card{ get; private set; }
        
        public Client(string name, string surname, string address=null, string id_card=null)
        {
            _id = Guid.NewGuid();
            
            _name = name;
            _surname = surname;
            _address = address;
            _id_card = id_card;
        }

        public void SetAddress(string address)
        {
            _address = address;
        }
        
        public void SetIdCard(string id_card)
        {
            _id_card = id_card;
        }

        public ClientId GetId()
        {
            return _id;
        }
        
    }
}