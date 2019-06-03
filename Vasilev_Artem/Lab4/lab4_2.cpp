#include <iostream>
#include <string>
#include <vector>

using namespace std;

int * prefix(string s)
{
    int *pi= new int[s.length()];
    pi[0]=0;
    int j = 0;
    for (int i=1; i < s.length(); i++ )
    {
        if (s[i] == s[j])
        {
            pi[i] = j+1;
            j++;
        }
        else if (j==0)
                pi[i] = 0;
            else
            {
                j = pi[j-1];
                i--;
            }
    }
    return pi;
}

int main()
{
    string p, t;
    cin >> t;
    cin >> p;
    string new_t = t + t;
    int find = -1;
    int * pi = prefix(p);
    for (int k = 0, l = 0; k < new_t.length(); k++)
    {
        if (new_t[k] == p[l])
        {
            l++;
            if (l == p.length()){
                find = k + 1 - p.length();
                break;
            }
        }
        else if(l != 0)
        {
            l = pi[l - 1];
            k--;
        }
    }

    if(t.size()!=p.size()) cout << "-1";
    else cout << find;
    
    delete [] pi;

    return 0;
}
