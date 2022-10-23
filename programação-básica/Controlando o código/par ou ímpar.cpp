#include <iostream>

using namespace std;

int main() {

  int Bino, Cino;

  cin >> Bino;
  cin >> Cino;

  if ((Bino + Cino) % 2 == 0)
    cout << "Bino";

  else
    cout << "Cino";

  return 0;
}
