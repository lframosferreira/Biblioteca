// Stoer Wagner
// https://dl.acm.org/doi/pdf/10.1145/263867.263872
// 
// encontra corte minimo em grafo conexo nao direcionado com pesos
// positivos
//
// O(VE + V²logV)

const int MAX = 110;

vector<ii> g[MAX];
int id[MAX];
int w[MAX];
int is_in_A[MAX];

int minimum_cut_phase(int a = 1){
    memset(is_in_A, 0, sizeof is_in_A);
    memset(w, 0, sizeof w);
    is_in_A[a]=1;
    vector<int> A = {a};
    int cnt=1;
}

