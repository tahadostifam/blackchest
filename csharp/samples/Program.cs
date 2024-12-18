public class InsertPersonException : Exception
{
    public InsertPersonException() : base("Failed to insert person into database") { }
}

class Program
{
    static void Main()
    {
        var personRepo = new Repository.PersonRepository();

        // Models.Person person = new Models.Person {
        //     FullName = "Serjio",
        //     Username = "serjio",
        //     Age = 34,
        // };
        // personRepo.InsertPerson(person);

        var persons = personRepo.GetPersons();

        foreach (var item in persons)
        {
            System.Console.WriteLine($"FullName: {item.FullName}, Username: {item.Username}, Age: {item.Age}");
        }
    }
}