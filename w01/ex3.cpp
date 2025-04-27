#include <iostream>
#include <string>
using namespace std;
void kBits(int k, char s[], int n) {
   if (n == k) {
       s[n] = '\0';
       cout << s << endl;
       return;
   }
   s[n] = '0';
   kBits(k, s, n + 1);
   s[n] = '1';
   kBits(k, s, n + 1);
}
void generateBinaryString (int k) {
   if (k <= 0) {
       return;
   }
   char s[100];
   kBits(k, s, 0);
}
int main() {
   int k;
   cin >> k;
   generateBinaryString(k);
}