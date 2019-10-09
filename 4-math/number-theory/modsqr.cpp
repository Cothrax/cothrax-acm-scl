ll modsqr(ll a, ll n)
{
    ll b, k, i, x;
    a = (a%n + n)%n;
    // printf("a=%lld\n", a);
    if(a == 0) return 0;
    if(n == 2) return a%n;
    if(Pow(a, (n-1)/2, n) == 1)
    {
        if(n%4 == 3) x = Pow(a, (n+1)/4, n);
        else
        {
            for(b = 1; Pow(b, (n-1)/2, n) == 1; b++);
            i = (n-1)/2;
            k = 0;
            do
            {
                i /= 2;
                k /= 2;
                if((Pow(a, i, n)*Pow(b, k, n)+1)%n == 0) k += (n-1)/2;
            }
            while(i%2 == 0);
            x = Pow(a, (i+1)/2, n) * Pow(b, k/2, n) % n;
        }
        if(x*2 > n) x = n - x;
        return x;
    }
    return -1;
}
