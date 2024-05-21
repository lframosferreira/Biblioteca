// Stoer Wagner
// https://dl.acm.org/doi/pdf/10.1145/263867.263872
// 
// encontra corte minimo em grafo conexo nao direcionado com pesos
// positivos
//
// O(VE + V²logV)


#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define sz(v)  (int)v.size()

#define dbg(x) cout << #x << " = " << x << endl

typedef long long ll;
typedef pair<int , int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<vd> vvd;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 110;

vector<vector<ii>> g;
int id[MAX];
int weights[MAX];
int rm[MAX];
int is_in_A[MAX];
int size_V;
int n, m;

int minimum_cut_phase(int a = 1){
    memset(is_in_A, 0, sizeof is_in_A);
    memset(weights, 0, sizeof weights);
    is_in_A[a]=1;
    vector<int> A = {a};
    int cnt=1;
    priority_queue<ii> pq;
    for (auto [w, v]: g[a]) if (!rm[v]){
        weights[v]=w;
        pq.push({weights[v], v});
    }
    
    while (cnt != size_V){
        auto [w, v] = pq.top();pq.pop();
        if (is_in_A[v] or rm[v]) continue;
        is_in_A[v]=1;
        A.pb(v);
        for (auto [we, viz]: g[v]) if (!rm[viz] and !is_in_A[viz]){
            weights[viz]+=we;
            pq.push({weights[viz], viz});
        } 
        cnt++;
    }
    
    int s = A[sz(A)-2];
    int t = A[sz(A)-1];
    // provavelmente tme um jeito mais eficiente de fzr isso
    map<int, int> idx_viz_s;
    for (int i = 0; i < sz(g[s]); i++){
        auto [w, v] = g[s][i];
        idx_viz_s[v]=i;
    }
    for (auto& [w, v] : g[t]){
        if (rm[v]) continue;
        if (idx_viz_s.count(v)){ // compartilham v
            int idx = idx_viz_s[v];
            g[s][idx].f+=w;
            for (auto& [a, b]: g[v]) if (b==s) a+=w;
        } else {
            g[s].pb({w, v}); 
            g[v].pb({w, s});
        }
    }
    rm[t]=1;
    return weights[t];
}

int stoer_wagner(){
    int mincut_val = INF;
    memset(rm, 0, sizeof rm);
    while (size_V > 1){
        int mcp = minimum_cut_phase();
        mincut_val=min(mincut_val, mcp);
        size_V--;
    }
    return mincut_val;
}

stack<tuple<int, int, int>> edges;

int main(){ _
    int t; cin >> t;
    while (t--){
        g.clear();
        cin >> n >> m;
        g.resize(n+1); 
        size_V=n;
        for (int i = 0; i < m; i++){
            int u, v, c; cin >> u >> v >> c;
            edges.push({u,v,c});
        }
        set<ii> foi;
        while (!edges.empty()){
            auto [u, v, c] = edges.top();edges.pop();
            if (foi.find({u, v}) != foi.end()) continue;
            foi.insert({u, v});
            foi.insert({v, u});
            g[u].pb({c, v});
            g[v].pb({c, u});
        }
        cout << stoer_wagner() << endl;
    }
    exit(0);
}
