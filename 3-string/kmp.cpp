/*
  kmp: find pattern t in text s
 */
void kmp(char *s, char *t)
{
    static int p[N];
    int n = strlen(s), m = strlen(t);
    
    p[0] = -1; int j = -1;
    rep(i, 1, m-1)
    {
        while(j >= 0 && t[j+1] != t[i]) j = p[j];
        if(t[j+1] == t[i]) j++;
        p[i] = j;
    }
    
    j = -1;
    rep(i, 0, n-1)
    {
        while(j >= 0 && t[j+1] != s[i]) j = p[j];
        if(t[j+1] == s[i]) j++;
        if(j == m-1)
        {
            printf("%d\n", i-m+1);
            j = p[j];
        }
    }
}
