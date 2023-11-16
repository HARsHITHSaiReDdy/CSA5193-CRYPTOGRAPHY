#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q, x0 = 0, x1 = 1;

    while (a > 1) {
        q = a / m;
        t = m, m = a % m, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}


int main() {
    int p, q, n, phi_n, e, d;

    printf("Enter the first prime number (p): ");
    scanf("%d", &p);

    printf("Enter the second prime number (q): ");
    scanf("%d", &q);

    n = p * q;
    phi_n = (p - 1) * (q - 1);

    printf("An integer e such that 1 < e < %d and gcd(e, f(n)) = 1: ", phi_n);
    for(int i=2;i<phi_n;i++)
    {
    	int length= phi_n%i;
    	if(!length==0)
    	{
    		e=i;
    		break;
		}
	}
   

    if (gcd(e, phi_n) != 1) {
        printf("e and f(n) are not coprime. Choose a different e.\n");
        return 1;
    }

    d = mod_inverse(e, phi_n);

    printf("Public Key: (n = %d, e = %d)\n", n, e);
    printf("Private Key: (n = %d, d = %d)\n", n, d);

    int m;

    printf("Enter the message to be encrypted: ");
    scanf("%d", &m);

    int c = (int)pow(m, e) % n;

    printf("Original Message: %d\n", m);
    printf("Encrypted Message: %d\n", c);

    int decrypted_message = (int)pow(c, d) % n;

    printf("Decrypted Message: %d\n", m);

    return 0;
}