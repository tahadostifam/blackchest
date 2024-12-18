using System.Data.SQLite;
using Dapper;
using Models;

namespace Repository
{
    public sealed class Connection()
    {
        private static readonly Lazy<SQLiteConnection> conn = new Lazy<SQLiteConnection>(() =>
        {
            Console.WriteLine("Connection with SQLite3 database established.");
            var db = new SQLiteConnection("Data Source=my.db;Version=3");
            db.Open();
            return db;
        });

        public static SQLiteConnection Instance = conn.Value;

        public void CloseConnection()
        {
            Instance.Close();
        }
    }

    public class PersonRepository
    {
        private SQLiteConnection conn = Connection.Instance;

        public void InsertPerson(Person person)
        {
            string insertSql = "INSERT INTO Persons (FullName, Username, Age) VALUES(@FullName, @Username, @Age)";
            var command = new SQLiteCommand(insertSql, conn);
            command.Parameters.AddWithValue("@FullName", person.FullName);
            command.Parameters.AddWithValue("@Username", person.Username);
            command.Parameters.AddWithValue("@Age", person.Age);
            int rowsAffected = command.ExecuteNonQuery();

            if (rowsAffected == 0)
            {
                throw new InsertPersonException();
            }
        }

        public List<Person> GetPersons()
        {
            var query = "SELECT * from Persons";
            List<Person> persons = new List<Person>();

            var command = new SQLiteCommand(query, conn);
            var reader = command.ExecuteReader();

            while (reader.Read())
            {
                string fullName = reader.GetString(0);
                string username = reader.GetString(1);
                int age = reader.GetInt32(2);
                
                persons.Add(new Person {
                    FullName = fullName,
                    Username = username,
                    Age = age
                });
            }

            return persons;
        }
    }
}