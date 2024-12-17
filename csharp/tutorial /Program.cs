class MyCustomException : Exception {
    public MyCustomException(string msg) 
    {
        System.Console.WriteLine(msg);
    }
}

class MyProgram
{
    static void Main()
    {
        try
        {
            throw new MyCustomException("Error Message");
        }
        catch (System.Exception e)
        {
            
            System.Console.WriteLine(e.Source);
        }
    }
}