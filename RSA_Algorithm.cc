// RSA Assignment for ECE4122/6122 Fall 2015

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Implement the RSA_Algorithm methods here

// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Fill in the remainder of the RSA_Algorithm methods
void RSA_Algorithm::GenerateRandomKeyPair(size_t sz)
{
  
  // get p and q
  mpz_class p, q;
  //get a random prime p of sz bits
  do
  {
  	p = rng.get_z_bits(sz);
  }
  while( !(mpz_probab_prime_p(p.get_mpz_t(), 100))); // keep executing if not prime

  //get a prime q of sz bits
  do
  {
	q = rng.get_z_bits(sz);
  }
  while( !(mpz_probab_prime_p(q.get_mpz_t(), 100))); // keep executing if not prime

  // now compute n
   
  n = p * q;

  // now compute phi_n
  mpz_class phi_n; 
  phi_n = (p - 1) * (q - 1);
    

  mpz_class gcd;
  int flag = 0;
  do
  {
  	d = rng.get_z_bits(sz * 2);
	if(d < phi_n)
	{
		mpz_gcd(gcd.get_mpz_t(), d.get_mpz_t(), phi_n.get_mpz_t());
		if (gcd == 1) flag = 1;
	}
  }
  while(flag == 0); // continue till flag = 1

  // compute e as multiplicative inverse of d mod phi_n
  mpz_invert(e.get_mpz_t(), d.get_mpz_t(), phi_n.get_mpz_t());
  //int inv_flag = 0;
  //inv_flag = mpz_invert(e.get_mpz_t(), d.get_mpz_t(), phi_n.get_mpz_t());
  //if(inv_flag != 0); // inverse exists
}


//Encrypt message M using public key (n,e) and return ciphertext C
mpz_class RSA_Algorithm::Encrypt(mpz_class M)
{
  mpz_class C;
  mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
  return C;
}


// Decrypt ciphertext C using private key (n,d) and return decrypted message M
mpz_class RSA_Algorithm::Decrypt(mpz_class C)
{
  mpz_class M;
  mpz_powm(M.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
  return M; 
}

void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}




