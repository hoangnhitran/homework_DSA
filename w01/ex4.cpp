#include <iostream>
using namespace std;
void towerOfHanoi(int n, char fromRod, char auxRod, char toRod) {
   if (n == 0) {
       return;
   }
   towerOfHanoi(n - 1, fromRod, toRod, auxRod);
   cout << "Disk " << n << " moved from " << fromRod << " to " << toRod << endl;
   towerOfHanoi(n - 1, auxRod, fromRod, toRod);
}
int main() {
   int n;
   cin >> n;
   towerOfHanoi(n, 'A', 'B', 'C');
}