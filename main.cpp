#include <iostream>
#include <list>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Grafo
{
private:
    int V; // número de vértices
    list<pair<int, int> > *adj; // ponteiro para um array contendo as listas de adjacências

public:

    // construtor
    Grafo(int V)
    {
        this->V = V; // atribui o número de vértices

        /*
            cria as listas onde cada lista é uma lista de pairs
            onde cada pair é formado pelo vértice destino e o custo
        */
        adj = new list<pair<int, int> >[V];
    }

    // adiciona uma aresta ao grafo de v1 à v2
    void addAresta(int v1, int v2, int custo)
    {
        adj[v1].push_back(make_pair(v2, custo));
    }

    // algoritmo de Dijkstra
    int dijkstra(int orig, int dest)
    {
        // vetor de distâncias
        int dist[V];

        /*
           vetor de visitados serve para caso o vértice já tenha sido
           expandido (visitado), não expandir mais
        */
        int visitados[V];

        // fila de prioridades de pair (distancia, vértice)
        priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        // inicia o vetor de distâncias e visitados
        for(int i = 0; i < V; i++)
        {
            dist[i] = INFINITO;
            visitados[i] = false;
        }

        // a distância de orig para orig é 0
        dist[orig] = 0;
        // insere na fila
        pq.push(make_pair(dist[orig], orig));

        // loop do algoritmo
        while(!pq.empty())
        {
            pair<int, int> p = pq.top(); // extrai o pair do topo
            int u = p.second; // obtém o vértice do pair
            pq.pop(); // remove da fila

            // verifica se o vértice não foi expandido
            if(visitados[u] == false)
            {
                // marca como visitado
                visitados[u] = true;

                list<pair<int, int> >::iterator it;
                int v;
                int custo_aresta;
//                cout<<"u vale "<<u<<endl;
                if(u<dest) {
                     for(it = adj[u].begin(); it != adj[u].end(); it++) {
                         v = it->first;
                         custo_aresta=it->second;
                         if (v == u + 1 && dist[v] > (dist[u] + custo_aresta)) {
                             dist[u + 1] = dist[u] + custo_aresta;
                             pq.push(make_pair(dist[v], v));
//                             cout << "pq " << dist[v] << " " << v << endl;
                             break;
                         }
                     }
                }
                else {
                    // percorre os vértices "v" adjacentes de "u"
                    for (it = adj[u].begin(); it != adj[u].end(); it++) {
                        v = it->first;
                        custo_aresta = it->second;
                            // relaxamento (u, v)
                            if (dist[v] > (dist[u] + custo_aresta)) {
                                // atualiza a distância de "v" e insere na fila
                                dist[v] = dist[u] + custo_aresta;
                                pq.push(make_pair(dist[v], v));
//                                cout<<"pq "<<dist[v]<<" "<<v<<endl;
                            }

                    }
                }
            }
        }

        // retorna a distância mínima até o destino
        return dist[dest];
    }
};

int main(int argc, char *argv[])
{
    int n,m,c,k;
    cin>>n>>m>>c>>k;
    while(n!=0 && m!=0 && c!=0 && k!=0) {
        Grafo g(n);
        int x,y,z;
        for (int i = 0; i < m; ++i) {
            cin>>x>>y>>z;
            g.addAresta(x,y,z);
            g.addAresta(y,x,z);
        }
        cout << g.dijkstra(k,c-1) << endl;
        cin>>n>>m>>c>>k;
    }
    return 0;
}
