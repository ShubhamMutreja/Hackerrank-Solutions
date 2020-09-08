#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

vector<long> par;
vector<long> size;
long find(long u)
{
    if(u == par[u])
    {
        return u;
    }
    return par[u] = find(par[u]);
}
void merge(long p1,long p2)
{
    if(size[p1] < size[p2])
    {
        par[p1] = p2;
        size[p2]+=size[p1];
    }
    else
    {
        par[p2] = p1;
        size[p1]+=size[p2];
    }
}
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    par.clear();
    size.clear();
    for(int i=0;i<=n;i++)
    {
        par.push_back(i);
        size.push_back(1);
    }
    for(auto &s : cities)
    {
        int u = s[0]; int v = s[1];
        int p = find(u); int q = find(v);
        if(p != q)
        {
            merge(p,q);
        }
    }
    long roads=0,libs=0;
    for(int i=1;i<=n;i++)
    {
        if(par[i] == i)
        {
            libs++;
            roads+=size[i]-1;
        }
    }
    cout<<roads-1<<libs<<endl;
    long cost1 = (roads)*c_road + libs*c_lib;
    long cost2 = c_lib*n;
    return min(cost1,cost2);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
