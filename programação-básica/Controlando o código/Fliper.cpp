#include <iostream>

using namespace std;

int main() {

  int P, R;

  cin >> P >> R;

  if (P == 0)
    cout << "C";

  else {

    if (R == 0)
      cout << "B";

    else
      cout << "A";
  }

  return 0;
}
