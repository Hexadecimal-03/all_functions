#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Edge // Basic class of edge with source, neighbour and weight as attributes
{
public:
    int src;
    int nbr;
    int wt;

    Edge(int src, int nbr, int wt)
    {
        this->src = src;
        this->nbr = nbr;
        this->wt = wt;
    }
};

bool haspath(vector<Edge> graph[], vector<bool> &visited, int src, int dest)
{
    /**
     * Takes in graph vector of vector of edges with edges having src as source as the 'at' value of vector of edges.
     * visited is the 1D vector <bool> with default value false and 'at' represents the vertex.
     * The function inputs above two parameters along with source and destination numbers ans returns 'True' if there exists a path btween them else 'False'.
     */

    if (src == dest)
    {
        return true;
    }

    visited[src] = true;

    for (Edge ed : graph[src])
    {
        if (visited[ed.nbr] == false and haspath(graph, visited, ed.nbr, dest))
        {
            return true;
        }
    }

    return false;
}

void printpath(vector<Edge> graph[], int src, int dest, vector<bool> visited, string ans)
{
    /**
     * Prints all paths in lexiographical order from src to dest.
     * Stores the temporary answer in the string ans for each branch of the recursion call.
     * The branches that lead to an answer, gets printed others get dropped off.
     */

    if (src == dest)
    {
        ans = ans + to_string(dest);
        cout << ans << endl;
        return;
    }

    visited[src] = true;

    for (Edge ed : graph[src])
    {
        if (!visited[ed.nbr])
        {
            char ch = src + '0';
            printpath(graph, ed.nbr, dest, visited, ans + ch);
        }
    }
    visited[src] = false;
}

void dfs(vector<Edge> graph[], int src, vector<bool> &visited)
{
    //Depth first traversal of the graph from src as source, here function just puts the visited value 'True' if the vertex is searched upon.

    visited[src] = true;

    for (Edge ed : graph[src])
    {
        if (visited[ed.nbr] == true)
        {
            continue;
        }
        dfs(graph, ed.nbr, visited);
    }
}

void dfs (vector <vector <int>> &arr, vector <vector <bool>> &visited, int i, int j)
{
    //The graph is in the form of the 2D array with 0 representing the edge and 1 representing the blockage (or no edge).
    //In the case of islands 0 is the land and 1 is the water.

    if (i < 0 or j < 0 or i >= arr.size() or j >= arr[0].size() or arr[i][j] == 1 or visited[i][j])     //ordering does matter (otherwise error may be encountered)
    {
        return;
    }

    visited[i][j] = true;
    dfs (arr, visited, i+1, j);
    dfs (arr, visited, i, j+1);
    dfs (arr, visited, i-1, j);
    dfs (arr, visited, i, j-1);

    return;
}

int islands (vector <vector <int>> &arr, vector <vector <bool>> &visited)
{
    /**
     * Returns number of islands in a graph.
     * The graph is in the form of 2D array with 0 representing the land and 1 representing the water.
     * The function uses the dfs to mark all the connected land as visited and increments the count when new land is encountered.
    */

    int i, j, count = 0;

    for (i = 0; i < arr.size(); ++i)
    {
        for (j = 0; j < arr[0].size(); ++j)
        {
            if (!visited[i][j] and arr[i][j] == 0)      //if new land is encountered
            {
                count++;
                dfs (arr, visited, i, j);
            }
        }
    }

    return count;
}

bool isNeighbour (std :: vector <Edge> graph[], int src, int dest)
{
    /**
     * Returns true if dest is direct neighbour of src and false if not.
     * Is used with function hamiltonianPathAndCycle
    */

    for (Edge ed : graph[src])
    {
        if (ed.nbr == dest)
        {
            return true;
        }
    }

    return false;
}

void hamiltonianPathAndCycle (std :: vector <Edge> graph[], std :: vector <bool> visited, int src, int vtces, std :: string asf, int source)
{
    /**
     * Prints all the hamiltonian paths possible from src as source.
     * A hamiltonian path is such which visits all vertices without visiting any twice.
     * A hamiltonian path becomes a cycle if there is an edge between first and last vertex.
     * The path is ended by '.' and cycle is ended by '*'.
     * dfs is used to traverse in graph and graph is in the form of vector of vectors (see above for documentation)
    */

    if (vtces == 1)     //When number of vertices are exhausted #base case
    {
        asf += std :: to_string (src);

        if (isNeighbour (graph, source, src))       //case for being a cycle for hamiltonian path
        {
            std :: cout << asf << "*" << std :: endl;
        }
        else
        {
            std :: cout << asf << "." << std :: endl;
        }
        return;
    }

    visited[src] = true;        //the vertex has been visited and hence marked true

    for (Edge ed : graph[src])
    {
        if (!visited[ed.nbr])
        {
            hamiltonianPathAndCycle (graph, visited, ed.nbr, vtces-1, asf + std :: to_string (src), source);
        }
    }

    visited[src] = false;       //backtracking to remove any chance of bug
}

class path  //Helper class for printpathsbfs function stores the source and the path so far.
{
    public:
    int src = 0;
    string psf = "";

    path (int num, string str)
    {
        this->src = num;
        this->psf = str;
    }
};

void printpathsbfs (int src, vector<vector<Edge>> graph, int vtces)
{
    /**
     * Uses bradth first search to print all the paths possible ti each vertex from the source.
     * The input graph is in the form of vector of vectors of edges.
     * The printed path is in the form of vertex + "@" + path to the vertex from source.
     * The queue id implemented for the bfs.
    */
    queue<path> que;
    vector<bool> visited (vtces, false);
    que.push(path(src, to_string(src)));


    while (!que.empty())
    {
        path f = que.front();
        visited[f.src] = true;
        
        cout << f.src << "@" << f.psf << endl;

        for (Edge ed : graph[f.src])
        {
            if (!visited[ed.nbr])
            {
                que.push(path(ed.nbr, f.psf + to_string(ed.nbr)));
                visited[ed.nbr] = true;
            }
        }
        que.pop();
    }
}

class Path
{
    /**
    * Helper class for shortestPathWts function, stores the source, weight covered till now and the path.
    * The path is in form of string, by default wt = 0 and string path is empty string.
    */

    public:
    int src;
    int wt = 0;
    std :: string path = "";

    Path (int source, int weight, std :: string pathway)
    {
        this->src = source;
        this->wt = weight;
        this->path = pathway;
    }
};

auto compare = [](Path a, Path b)
{
    /**
     * The class is for the priority queue.
     * The compare class is using operator overloading of "[]" over "()".
     * The class have inputs in form of Path class which have a instance of weight i.e., weight so far.
     * The lower weight is given priority.
    */

    return a.wt > b.wt;
};

void shortestPathWts (int src, std :: vector <Edge> graph[], int vtces)
{
    /**
     * The function takes in source vertex and prints all the paths to the vertices remaining.
     * The function is similar to the printpathbfs function, but instead of queue this function uses a priority queue,
     * The function print paths in ascending order according the weights of the paths.
     * For the purpose, it uses a class "Path" and a custom comparator class "compare" that prioritises the smaller weight of Path.
    */

    std :: vector <bool> visited (vtces, false);
    std :: priority_queue <Path, std :: vector <Path>, decltype(compare)> pq (compare);
    pq.push (Path (src, 0, std :: to_string (src)));

    while (!pq.empty())
    {
        Path f = pq.top();
        pq.pop();

        if (visited[f.src])
        {
            continue;
        }

        std :: cout << f.src << " via " << f.path << " @ " << f.wt << std :: endl;

        visited[f.src] = true;

        for (Edge ed : graph[f.src])
        {
            if (!visited[ed.nbr])
            {
                pq.push (Path (ed.nbr, f.wt + ed.wt, f.path + std :: to_string (ed.nbr)));
            }
        }
    }
}

std :: vector <std :: vector <int>> connectedComponents (std :: vector <Edge> graph[], int vtces)
{
    /**
     * The function takes in a graph in form of vector of vectors.
     * The graph is like islands and some of the components are connected and some are not connected
     * The function returns a vector <vector <int>> comps with vector of islands and island is vector of connected integers.
     * The function is non-recursive and uses a queue of int for the implementation of the same.
    */
    int i;
    std :: vector <bool> visited (vtces, false);
    std :: vector <std :: vector <int>> comps; 
    for (i = 0; i < vtces; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        std :: queue <int> que;
        que.push (i);
        visited[i] = true;

        std :: vector <int> ans;
        while (!que.empty())
        {
            int f = que.front();
            que.pop();
            ans.push_back (f);

            for (Edge ed : graph[f])
            {
                if (!visited[ed.nbr])
                {
                    que.push (ed.nbr);
                    visited[ed.nbr] = true;
                }
            }
        }
        comps.push_back (ans);
    }

    return comps;
}


int main()
{
    /**
     * A method to create a graph and take input edge by edge in it.
     * The graph is made as a vector of vectors of class Edge with 'at' representing the source value.
     * The graph takes in value as Edge with src, dest and weight as parameters of the edge.
     * graph vector has number of vectors equal to number of vertices and sum of all equal to number of Edges*2.
     */

    int vtces;
    cin >> vtces;
    vector<Edge> graph[vtces]; // graph is made as vector of vectors number of vectors are equal to vtes.

    int edges;
    cin >> edges;
    for (int i = 0; i < edges; i++)
    {
        int v1; // Vertex 1 can be source or destination, doesn't matter for the two way graphs.
        int v2; // The ordering would have mattered if the graph was one sided.
        int wt;
        cin >> v1 >> v2 >> wt;
        graph[v1].push_back(Edge(v1, v2, wt)); // Valid for two sided graphs where source to dest has same edge as dest to source.
        graph[v2].push_back(Edge(v2, v1, wt)); // Hence one Edge represents the path for both the edges also the weight is also same.
    }

    vector<bool> visited(edges, false); // A boolean vector to store the visited vertices in a traversal (default set to 'false' for every vertex)

    return 0;
}