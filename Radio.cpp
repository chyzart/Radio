#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void DFS(int s, vector<vector<int>> & Edges, int & num, vector <int> & colour, bool & ans);
bool checker(int & num, vector<long double> & X, vector<long double> & Y, long double dist);

int main()
{
    const long double EPS = pow(10, -12);
    int num = 0;
    cin >> num;
    vector<long double> X(num);
    vector<long double> Y(num);
    for (int i = 0; i < num; ++i)
        cin >> X[i] >> Y[i];
    long double l = 0;
    long double r = 100000;
    long double mid;
    while (l + EPS <= r)
    {
        mid = (r + l) / 2;
        if (checker(num, X, Y, mid))
            l = mid;
        else
            r = mid;
    }
    cout.precision(15);
    cout << r << endl;
    vector <vector<int>> C;
    C.resize(num, vector<int>(num));
    long double delta_x, delta_y;
    for (int i = 0; i < num; ++i)
    {
        for (int j = i + 1; j < num; ++j)
        {
            delta_x = X[i] - X[j];
            delta_y = Y[i] - Y[j];
            if (sqrt(delta_x * delta_x + delta_y * delta_y) < 2 * l)
            {
                C[i][j] = 1;
                C[j][i] = 1;
            }
        }
    }
    vector<int> colour1(num);
    bool check = true;
    bool ans = true;
    int i;
    while (check)
    {
        i = 0;
        for (; i < num && colour1[i] > 0; ++i){}
        if (i < num)
        {
            colour1[i] = 1;
            DFS(i, C, num, colour1, ans);
        }
        else
            check = false;
    }
    for (int i = 0; i < num; ++i)
        cout << colour1[i] << " ";
    return 0;
}
bool checker(int & num, vector<long double> & X, vector<long double> & Y, long double dist)
{
    vector<vector<int>> Edges;
    long double delta_x, delta_y;
    Edges.resize(num, vector<int>(num));
    for (int i = 0; i < num; ++i)
    {
        for (int j = i + 1; j < num; ++j)
        {
            delta_x = X[i] - X[j];
            delta_y = Y[i] - Y[j];
            if (sqrt(delta_x * delta_x + delta_y * delta_y) < 2 * dist)
            {
                Edges[i][j] = 1;
                Edges[j][i] = 1;
            }
        }
    }
    bool ans = true;
    vector<int> colour(num);
    bool check = true;
    int i;
    while (check)
    {
        i = 0;
        for (; i < num && colour[i] > 0; ++i){}
        if (i < num)
        {
            colour[i] = 1;
            DFS(i, Edges, num, colour, ans);
        }
        else
            check = false;
    }
    return ans;
    return 0;
}
void DFS(int s, vector<vector<int>> & Edges, int & num, vector<int> & colour, bool & ans)
{
    for (int i = 0; i < num; ++i)
    {
        if (Edges[s][i] == 1)
        {
            if (colour[i] == colour[s])
                ans = false;
            if (colour[i] == 0)
            {
                colour[i] = 3 - colour[s];
                DFS(i, Edges, num, colour, ans);
            }
        }
    }
}
