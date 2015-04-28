#ifndef _H_GRAPH_
#define _H_GRAPH_

#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

typedef std::pair <int, int> pii;
typedef std::function <void(int const&)> visit_nodes;
typedef std::function <void(pii const&)> visit_edges;

template <typename Node>
class Graph {
public:
	Graph() = default;
	~Graph() = default;
    int add_node();
    void add_edge(int const& v, int const& u);
	void visit_every_node(visit_nodes const& visitor) const;
	void visit_every_edge(int const& source, visit_edges const& visitor);
	size_t get_nodes_size() const;
    void read(std::string const& filename);
    void print(std::string const& filename);
	int move(int const& origin, pii const& edge);
	Node & operator[](int const& node);
	void dfs(visit_nodes const& start, visit_nodes const& end, visit_nodes const& dfs_go);
private:
	friend class boost::serialization::access;
	void clear();
	std::vector < std::vector <int> > vert;
	std::vector <Node> payloads;
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version);
	Node defaultPayload; 
};

#endif //_H_GRAPH_
