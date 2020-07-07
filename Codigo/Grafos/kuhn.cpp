// Algoritmo de Kuhn
//
// Computa matching maximo em grafo bipartido
// 'n' e 'm' sao quantos vertices tem em cada particao
// chamar add(i, j) para add aresta entre o cara i
// da particao A, e o cara j da particao B
// (entao i < n, j < m)
// Para recuperar o matching, basta olhar 'ma' e 'mb'
// cover() retorna o min vertex cover como um par de
// {caras da particao A, caras da particao B}
//
// O(n m)
// Na pratica, parece rodar tao rapido quanto o Dinic

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct kuhn {
	int n, m;
	vector<vector<int>> g;
	vector<int> vis, ma, mb;

	kuhn(int n_, int m_) : n(n_), m(m_), g(n),
		vis(n+m), ma(n, -1), mb(m, -1) {}

	void add(int a, int b) { g[a].pb(b); }

	bool dfs(int i) {
		vis[i] = 1;
		for (int j : g[i]) if (!vis[n+j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int matching() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (aum) {
			for (int j = 0; j < m; j++) vis[n+j] = 0;
			aum = 0;
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 and dfs(i)) ret++, aum = 1;
		}
		return ret;
	}
	pair<vector<int>, vector<int>> cover() {
		int M = matching();
		for (int i = 0; i < n+m; i++) vis[i] = 0;
		for (int i = 0; i < n; i++) if (ma[i] == -1) assert(!dfs(i));
		vector<int> ca, cb;
		for (int i = 0; i < n; i++) if (!vis[i]) ca.push_back(i);
		for (int i = 0; i < m; i++) if (vis[n+i]) cb.push_back(i);
		//assert(ca.size() + cb.size() == M);
		return {ca, cb};
	}
};
