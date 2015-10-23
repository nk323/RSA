// ECE4122/6122 RSA Encryption/Decryption assignment
// Neha Kadam
// Fall Semester 2015

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  
  // Loop from sz = 32 to 1024 inclusive
  // for each size choose 10 different key pairs
  // For each key pair choose 10 differnt plaintext 
  // messages making sure it is smaller than n.
  // If not smaller then n then choose another
  // For eacm message encrypt it using the public key (n,e).
  // After encryption, decrypt the ciphertext using the private
  // key (n,d) and verify it matches the original message.

  // your code here


  size_t sz = 32;


  // double size for every iteration upto and including 1024
  for(sz = 32; sz < 1025; sz *= 2)
  {
	// for each sz generate 10 key pairs
	for(int i = 0; i < 10; i++)
	{
		RSA.GenerateRandomKeyPair(sz);
		RSA.PrintNDE();
		mpz_class plaintext;
		// for each key pair generate 10 plaintext messages
		for(int j = 0; j < 10; j++)
		{
			
			// generate a random message less than n 
			do
			{
				plaintext = RSA.rng.get_z_bits(sz*2 - 1);//any arbitrary size < n
			}
			while(!(plaintext < RSA.n)); //keep trying till message < n

			//print plaintext message
			RSA.PrintM(plaintext);
			// encrypt plain text message
			mpz_class ciphertext;
			ciphertext = RSA.Encrypt(plaintext);
			// print ciphertext
			RSA.PrintC(ciphertext);

			// decrypt ciphertext
			mpz_class decrypted_msg;
			decrypted_msg = RSA.Decrypt(ciphertext);
			
			//confirm decrypted message is same as plaintext
			//RSA.PrintM(decrypted_msg);
			//if(decrypted_msg == plaintext) printf("Matched.");
			//else printf("Wrong!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		}
	}
  }

  
} 
