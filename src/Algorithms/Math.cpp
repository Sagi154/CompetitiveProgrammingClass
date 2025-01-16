#include "../headers.h"
#include "extendedGcd.cpp"

ll modularInverse(ll a, ll mod){
    ll x, y;

    extendedGcd(a,mod,x,y);
    return x;
}

ll modExp(ll base, ll exp, ll mod)
{
    ll result = 1; // Initialize result
    base = base % mod;    // Update base if it's more than or equal to mod

    while (exp > 0)
    {
        // If exp is odd, multiply base with the result
        if (exp % 2 == 1)
            result = (result * base) % mod;

        // Now exp must be even, divide it by 2
        exp = exp >> 1;             // Equivalent to exp /= 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

#include "../headers.h"

// Function for extended Euclidean Algorithm
ll extendedGcd(ll a, ll b, ll &x, ll &y)
{
    // Base Case
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    ll x1, y1; // To store results of recursive call
    ll gcd = extendedGcd(b % a, a, x1, y1);

    // Update x and y using results of
    // recursive call
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

ll gcd(ll a, ll b)
{
    ll x, y;
    return extendedGcd(a, b, x, y);
}

ll lcm(ll a, ll b)
{
    return a * b / gcd(a, b);
}
