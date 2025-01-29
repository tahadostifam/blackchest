struct Sample {
  char *name
};

struct Sample sample = { .name = "Hello World" };


int main()
{
  sample();
  
  return (int)0;
}
