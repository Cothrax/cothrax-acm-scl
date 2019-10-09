/*
  manacher
  var:  str[N]          : 原字符串
        s[N]            : 扩充后的字符串
        rad[N]          : 回文半径
  func: manacher(n)     : manacher(字符串长度)
  note: 以i为中心的回文串最大长度为f[i]-1
 */

const int N = 105;
int rad[N]; char s[N], str[N];
void manacher(int n)
{
    s[0] = '('; s[1] = '#'; s[2*n+2] = ')';
    for(int i = 0; i < n; i++) s[i*2+2] = str[i], s[i*2+3] = '#';
    n = 2*n+3;
    
    int r = 0, mid;
    for(int i = 1; i < n; i++)
    {
        rad[i] = i<r ? min(rad[(mid<<1)-i], rad[mid]+mid-i) : 1;
        while(s[i+rad[i]]==s[i-rad[i]]) rad[i]++;
        if(rad[i] + i > r) r = rad[i] + i, mid = i;
        
        // 长度len, 在原串中中心为center
        int len = rad[i]-1, center = i/2-1;
        if(len)
        {
            int lp = center - ceil((len-2)/2.0),
                rp = center + len/2;
            // 在原串中区间为 [lp, rp]
        }
    }
}

