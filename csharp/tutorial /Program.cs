public class TextBox
{
    public event EventHandler<TextChangedEventArgs> TextChanged;

    protected virtual void OnTextChanged(TextChangedEventArgs e)
    {
        if (TextChanged != null)
        {
            TextChanged(this, e);
        }
    }
}

public class TextChangedEventArgs : EventArgs
{
    public string NewText { get; set; }

    public TextChangedEventArgs(string newText)
    {
        NewText = newText;
    }
}

class MyProgram
{
    public delegate void Callback(String input);

    private static void TextBox_TextChanged(object sender, TextChangedEventArgs e)
    {
        Console.WriteLine("text changed: "+ e.NewText);
    }
    
    public static void Main(string[] args)
    {
        TextBox textBox = new TextBox();

        textBox.TextChanged += TextBox_TextChanged;
        

        // Action<object> objectAction = obj =>
        // {
        //     Console.WriteLine(obj);
        // };
        //
        // Action<object> a = new Action<object>(objectAction);
        //
        // a.Invoke(1234);
    }
}