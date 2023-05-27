//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa6
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "535893475837489573498758378";
   string s3 = "402398498329948493280432940";
   string s5 = "354298935890248595739284903";

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger C = BigInteger(s5);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   A.negate();

   BigInteger D = A+B;
   BigInteger E = B-A;
   BigInteger F = A*B;

   cout << endl;


   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;

   return EXIT_SUCCESS;
}