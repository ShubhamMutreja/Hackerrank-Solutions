#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
vector<string> split_string(string);
// Complete the journeyToMoon function below
ll gcc(int src,vector<vector<int>> &graph,vector<bool> &vis)
{
    vis[src] = true;
    ll c = 1;
    for(int e : graph[src])
    {
        if(!vis[src])
        {
            
            c+=gcc(e,graph,vis);
        }
    }
    return c;
}
ll journeyToMoon(int n, vector<vector<int>> astronaut) {
    // make graph]
    vector<vector<int>> graph(n,vector<int>());

    for(int i=0;i<astronaut.size();i++)
    {
        graph[astronaut[i][0]].push_back(astronaut[i][1]);
        graph[astronaut[i][1]].push_back(astronaut[i][0]);
        
    }
    vector<bool> vis(n,false);
    vector<int> p;
    for(int i=0;i<n;i++)
    {
        if(!vis[i])
        {
            int g = gcc(i,graph,vis);
            p.push_back(g);
        }
    }
    long Y = accumulate(p.begin(),p.end(),0);
    

    long ans=0;
    for(int ele : p)
    {
        ans += ele*(Y - ele);
        Y = Y - ele;
       // cout<<ele;
    }
    return ans;
     
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string np_temp;
    getline(cin, np_temp);

    vector<string> np = split_string(np_temp);

    int n = stoi(np[0]);

    int p = stoi(np[1]);

    vector<vector<int>> astronaut(p);
    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> astronaut[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ll result = journeyToMoon(n, astronaut);

    fout << result << "\n";

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
