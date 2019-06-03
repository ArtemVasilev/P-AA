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
    cin >> p;
    cin >> t;
    vector <size_t> find;
    int * pi = prefix(p);
    for (int k = 0, l = 0; k < t.length(); k++)
    {
        if (t[k] == p[l])
        {
            l++;
            if (l == p.length())
                find.push_back(k + 1 - p.length());
        }
        else if(l != 0)
        {
            l = pi[l - 1];
            k--;
        }
    }

    if(find.empty())
        cout << "-1";
    else {
        for (int i = 0; i < find.size()-1; i++)
            cout << find[i] << ",";
        cout << find[find.size() - 1];
    }
    
    delete [] pi;

    return 0;
}
