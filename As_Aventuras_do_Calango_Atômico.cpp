//referência do algoritmo: https://gist.github.com/marcoscastro/d4e0df5b134c2cd63cf2

#include <iostream>
#include <list>
#include <queue>
#define INFINITO 1000000000001

using namespace std;

class Grafo {
private:
	int V;
	list<pair<int, int> > * adj;

public:

	Grafo(int V) {
		this->V = V;
		adj = new list<pair<int, int> >[V];
	}

	void addAresta(int v1, int v2, int custo) {
		adj[v1].push_back(make_pair(v2, custo));
	}

	long long int dijkstra(int orig, int dest) {
		long long int dist[V];
		int visitados[V];
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		for(int i = 0; i < V; i++) {
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		dist[orig] = 0;

		pq.push(make_pair(dist[orig], orig));

		while(!pq.empty()) {
			pair<int, int> p = pq.top();
			int u = p.second;
			pq.pop();

			if(visitados[u] == false) {
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				for(it = adj[u].begin(); it != adj[u].end(); it++) {
					int v = it->first;
					int custo_aresta = it->second;

					if(dist[v] > (dist[u] + custo_aresta)) {
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		return dist[dest];
	}
};

int main(void) {
    int F, C, T, A, B, D;
	long long int dist_total=0;
    scanf("%d", &F);
    for(int i=0; i<F; i++) {
        scanf("%d %d", &C, &T);
        Grafo *G = new Grafo((C+1));
        for(int j=0; j<T; j++) {
            scanf("%d %d %d", &A, &B, &D);
            G -> addAresta(A, B, D);
        }
        dist_total += G -> dijkstra(1, C);
    }
    cout << dist_total << endl;
}