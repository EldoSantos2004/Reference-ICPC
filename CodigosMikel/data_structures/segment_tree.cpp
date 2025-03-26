int x[400000] = {1000000001};
int n;
void update(int a, int b)
{
  a += n;
  x[a] = b;
  for (a /= 2; a >= 1; a /= 2)
  {
    x[a] = min(x[a * 2], x[a * 2 + 1]);
  }
}
int find(int a, int b)
{
  a += n;
  b += n;
  int s = 1000000000;
  while (a <= b)
  {
    if (a % 2 == 1)
      s = min(s, x[a++]);
    if (b % 2 == 0)
      s = min(s, x[b--]);
    a /= 2;
    b /= 2;
  }
  return s;
}