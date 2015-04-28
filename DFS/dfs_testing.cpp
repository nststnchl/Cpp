#include <gtest/gtest.h>

#include "Graph.cpp"

TEST(correctness, my_constructor)
{
    Graph <int> g = Graph <int> ();
    int n = (int) g.get_nodes_size();
    
    EXPECT_TRUE(n == 0);
}

TEST(correctness, 1_node)
{
    Graph <int> g = Graph <int> ();
    g.add_node();
    EXPECT_TRUE(g.get_nodes_size() == 1);
}

namespace
{
    const int n = 500;
    Graph <int> g;
    int * colors;
    int color;
    char good;
    int curr;
    std::vector <int> v;

    void init(int n)
    {
        g = Graph <int> ();
        
        for (int i = 0; i < n; i++)
            g[g.add_node()] = (size_t) i;
        
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                g.add_edge(size_t (i), size_t (j));
    }

    void visit(pii const& e)
    {
        v.push_back((e.first == curr) ? g[e.second] : g[e.first]);
    }

    char isFull()
    {
        if (n != (int) v.size() + 1)
            return 0;

        for (int i = 0; i < n; i++)
        {
            char exists = 0;

            for (int j = 0; j < (int) v.size(); j++)
                if (v[j] == i)
                {
                    exists = 1;
                    break;
                }

            if (exists || i == curr)
                continue;

            return 0;
        }

        return 1;
    }

    void go(int const& e)
    {
        v.clear();
        curr = e;
        g.visit_every_edge(e, visit);
        
        EXPECT_TRUE(isFull());
    }

    void init_1_node()
    {
        g = Graph <int> ();
        g.add_node();
    }

    void init_tree()
    {
        g = Graph <int> ();
        int prev, tmp;
        prev = g.add_node();

        for (int i = 1; i < n; i++)
        {
            tmp = g.add_node();
            g.add_edge(tmp, prev);
            prev = tmp;
        }
    }

    void init_graph_with_even_cycle()
    {
        g = Graph <int> ();
        int prev, tmp, start;
        prev = g.add_node();
        start = prev;

        for (int i = 1; i < n; i++)
        {
            tmp = g.add_node();
            g.add_edge(tmp, prev);
            prev = tmp;
        }

        g.add_edge(prev, start);
    }

    void init_graph_with_odd_cycle()
    {
        g = Graph <int> ();
        int prev, tmp, start;
        prev = g.add_node();
        start = prev;

        for (int i = 1; i <= n; i++)
        {
            tmp = g.add_node();
            g.add_edge(tmp, prev);
            prev = tmp;
        }

        g.add_edge(prev, start);
    }

    void start(int const& e)
    {
        if (!colors[e])
            colors[e] = color;
        else
            color = colors[e];
    }

    void end(int const& e)
    {
        color = 0;
    }


    void go_dfs(int const& e)
    {
        if (!color)
            throw new std::exception();

        if (colors[e] == color)
            good = 0;
        else if (!colors[e])
            colors[e] = color % 2 + 1;
    }

    char check()
    {
        colors = new int[g.get_nodes_size()];
        color = 1;

        for (int i = 0; i < g.get_nodes_size(); i++)
            colors[i] = 0;

        good = 1;
        g.dfs(start, end, go_dfs);

        delete[] colors;
        return good;
    }
}

TEST(correctness, dfs_1_node)
{
    init_1_node();
    EXPECT_EQ(1, check());
}

TEST(correctness, 5_nodes)
{
    Graph <int> gg = Graph <int> ();
    int nn = 5;
    
    for (int i = 0; i < nn; i++)
        gg.add_node();
    
    EXPECT_EQ(nn, gg.get_nodes_size());
}

TEST(correctness, 10_nodes)
{
    Graph <int> gg = Graph <int> ();
    int nn = 10;
    
    for (int i = 0; i < nn; i++)
        gg.add_node();
    
    EXPECT_EQ(nn, gg.get_nodes_size());
}

TEST(correctness, 10000_nodes)
{
    Graph <int> gg = Graph <int> ();
    int nn = 10000;
    
    for (int i = 0; i < nn; i++)
        gg.add_node();
    
    EXPECT_EQ(nn, gg.get_nodes_size());
}

TEST(correctness, random_nodes)
{
    int T = 3;
    srand (time (0));
    
    while (T --> 0)
    {
        Graph <int> gg = Graph <int> ();
        int nn = rand() % 30000 + 10;
        
        for (int i = 0; i < nn; i++)
            gg.add_node();
        
        EXPECT_EQ(nn, gg.get_nodes_size());
    }
}

TEST(correctness, full_graph)
{
    init(n);
    EXPECT_EQ(n, g.get_nodes_size());
    g.visit_every_node(go);
}

TEST(correctness, dfs_tree)
{
    init_tree();
    EXPECT_EQ(1, check());
}

TEST(correctness, dfs_graph_with_even_cycle)
{
    init_graph_with_even_cycle();
    EXPECT_EQ(1, check());
}

TEST(correctness, dfs_graph_with_odd_cycle)
{
    init_graph_with_odd_cycle();
    EXPECT_EQ(0, check());
}

TEST(correctness, files)
{
    init(n);
    g.print("graph");
    g = Graph <int> ();
    g.read("graph");
    
    EXPECT_EQ(n, g.get_nodes_size());
    g.visit_every_node(go);
}

TEST(correctness, exceptions)
{
    EXPECT_ANY_THROW(g[n]);
    EXPECT_ANY_THROW(g[-1]);
    EXPECT_ANY_THROW(g.visit_every_edge(n + 1, visit));
}
