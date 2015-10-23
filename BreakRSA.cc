// Grad student portion of the RSA assignment
// Neha Kadam
// Fall 2015 ECE6122

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main(int argc, char** argv)
{ // Arguments are as follows:
  //argv[1] = n;
  //argv[2] = e;  // n and e are the public key
  //argv[3] = first 6 characters of encrypted message
  //argv[4] = next 6 characters .. up to argv[12] are the lsat 6 characters
  // The number of arguments will always be exacty 12, and each argument past the
  // public key contain 6 ascii characters of the encrypted message.
  // Each of the 32bit values in the argv[] array are right justified in the
  // low order 48 bits of each unsigned long.  The upper 16 bits are always
  // zero, which insures the each unsigned long is < n (64 bits) and therefore
  // the RSA encryption will work.

  // Below is an example of the BreakRSA and command line arguments:

// ./BreakRSA  2966772883822367927 2642027824495698257  817537070500556663 1328829247235192134 
// 1451942276855579785 2150743175814047358 72488230455769594 1989174916172335943 962538406513796755 
// 1069665942590443121 72678741742252898 1379869649761557209

//   The corect output from the above is:
//   HelloTest  riley CekwkABRIZFlqmWTanyXLogFgBUENvzwHpEHRCZIKRZ
//
//   The broken (computed) private key for the above is 4105243553

  // Our one and only RSA_Algorithm object
  RSA_Algorithm rsa;
  
  // First "break" the keys by factoring n and computing d	
  // Set the keys in the rsa object afer calculating d
  rsa.n = mpz_class(argv[1]);
  rsa.e = mpz_class(argv[2]);
  mpz_class p, q, phi, d;

  // Set rsa.d to the calculated private key d
  // rsa.d = mpz_class(// broken d value here) 
  
  // Factorizing rsa.n using Pollard's Rho method
  mpz_class num = rsa.n;
  mpz_class c = rsa.rng.get_z_range(num);
  mpz_class x = rsa.rng.get_z_range(num);
  mpz_class y = x;
  p = 1;
  mpz_class z;

  while(p == 1) 
  {
	x = (x*x + c) % num;
	y = (y*y + c) % num;
	y = (y*y + c) % num;
	z = x - y;
	mpz_gcd(p.get_mpz_t(), z.get_mpz_t(), num.get_mpz_t());
  }

  // now p is a prime factor of n, find q
  q = rsa.n / p;
  //get phi
  phi = (p-1) * (q-1);
  //find d
  mpz_invert(d.get_mpz_t(), rsa.e.get_mpz_t(), phi.get_mpz_t());
  rsa.d = d;
  //rsa.PrintNDE();
  
  // Now to decrypt and display the message
  // array to hold shift positions 
  unsigned shift[] = {40, 32, 24, 16, 8, 0};
  unsigned long temp;
  char ch;
  
  for (int i = 3; i < 13; ++i)
  { // Decrypt each set of 6 characters
      mpz_class C(argv[i]);
      mpz_class m = rsa.Decrypt(C);
      //  use the get_ui() method in mpz_class to get the lower 48 bits of the m
      unsigned long ul = m.get_ui();
      // Now print the 6 ascii values in variable ul.  As stated above the 6 characters
      // are in the low order 48 bits of ui.

      // mask to extract the 5th byte
      unsigned long mask = 0x0000ff0000000000;
     
      for(int j = 0; j < 6; ++j) //because 6 ascii values in ul
      {
	temp = ul & mask;
	temp = temp >> shift[j];
  	ch = (char) temp;
	cout << ch;
	mask = mask >> 8;
      }
  }

  cout << endl;

}

