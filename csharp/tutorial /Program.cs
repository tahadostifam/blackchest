using Newtonsoft.Json;

public struct Person
{
    public string Name;
    public string LastName;
    public int Age;
    public DateTime BirthDate;
}

class MyProgram
{
    static void Main()
    {
        string json = @"{""Name"":""Jane Doe"",""Age"":25,""BirthDate"":""1998-03-15T08:00:00""}";
        Person person = JsonConvert.DeserializeObject<Person>(json);
        System.Console.WriteLine(person.Name);
        System.Console.WriteLine(person.LastName);
        System.Console.WriteLine(Convert.ToDouble(person.Age));
        System.Console.WriteLine(person.BirthDate);
    }
}