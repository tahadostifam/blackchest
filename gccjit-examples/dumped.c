extern int main ()
{
entry:
  if ((int)1 < (int)2) goto true_block_1; else goto false_block_1;

true_block_1:
  if ((int)10 == (int)10) goto true_block_2; else goto false_block_2;

false_block_1:
  if ((int)3 < (int)4) goto true_block_2; else goto final_block;

true_block_2:
  goto final_block;

false_block_2:
  goto final_block;

final_block:
  return (int)0;
}

