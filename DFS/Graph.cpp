#include "Graph.h"

template <typename Node>
int Graph <Node>::add_node()
{
	vert.push_back(std::vector <int>());
	payloads.push_back(defaultPayload);
	return (int) payloads.size() - 1;
}

template <typename Node>
void Graph <Node>::add_edge(int const& v, int const& u)
{
	if (v != u)
    {
        char found = 0;
        for (int i = 0; i < (int) vert[v].size(); i++)
            if (vert[v][i] == u)
            {
                found = 1;
                break;
            }
		if (!found)
			vert[v].push_back(u);
        found = 0;
        for (int i = 0; i < (int) vert[u].size(); i++)
            if (vert[u][i] == v)
            {
                found = 1;
                break;
            }
		if (!found)
			vert[u].push_back(v);
	}
}

template <typename Node>
void Graph<Node>::visit_every_node(std::function<void(int const &)> const & visitor) const
{
	for (int i = 0; i < (int) vert.size(); i++)
		visitor(i);
}

template <typename Node>
void Graph <Node>::visit_every_edge(int const & source, visit_edges const & visitor)
{
	if (source >= vert.size() || source < 0)
		throw new std::exception();

	for (auto it = vert[source].begin(); it != vert[source].end(); it++)
		visitor(std::make_pair(source, *it));
}

template <typename Node>
size_t Graph <Node>::get_nodes_size() const
{
	return vert.size();
}

template <typename Node>
Node & Graph <Node>::operator[](int const& node)
{
	if (node >= payloads.size() || node < 0)
		throw new std::exception();

	return payloads[node];
}

template <typename Node>
void Graph <Node>::dfs(visit_nodes const& start, visit_nodes const& end, visit_nodes const& go_dfs)
{
	char * used = new char[vert.size()];
    for (int i = 0; i < (int) vert.size(); i++)
        used[i] = 0;
	int curr;
	for (int i = 0; i < (int) vert.size(); i++) {
		if (!used[i]) {
			std::stack <int> st;
			st.push(i);
			while (!st.empty()) {
				curr = st.top();
				st.pop();
				start(curr);
				for (auto it = vert[curr].begin(); it != vert[curr].end(); it++)
                {
					go_dfs(*it);
					if (!used[*it])
                    {
						used[*it] = 1;
						st.push(*it);
					}
				}
				end(curr);
			}
		}
	}
	delete[] used;
}

template <typename Node>
int Graph <Node>::move(const int &origin, const pii &edge)
{
    return origin == edge.first ? edge.second : edge.first;
}
 
template <typename Node>
void Graph <Node>::clear()
{
	vert.clear();
	payloads.clear();
}

template <typename Node> template <class Archive>
void Graph <Node>::serialize(Archive& ar, const unsigned int version) 
{
    ar& vert;
    ar& payloads;
} 

template <typename Node>
void Graph <Node>::print(std::string const& filename)
{
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

template <typename Node>
void Graph <Node>::read(std::string const& filename)
{
    Graph g;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia >> g;
    vert = g.vert;
    payloads = g.payloads;
}
