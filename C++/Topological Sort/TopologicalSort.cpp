#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <vector>

/** The Vertex class that has the name and indegree of all vertices in the graph */
class Vertex
{
  public:
    /** The name of the vertex */
    std::string name;

    /** The indegree of the vertex */
    int indegree;

    /** A list of adjacent vertices to this Vertex object */
    std::vector<Vertex *> adjacentVertices;

    /**
     *  @brief Initializes a Vertex object.
     *  This constructor initializes a MiddleEarth object with
     *  the given name.
     *  @return None
     *  @param name The name of the vertex
     */
    Vertex(std::string name)
    {
        this->name = name;
        indegree = 0;
    }

    /**
     *  @brief Adds an adjacent vertex to adjacentVertices.
     *  This function adds an adjacent vertex to adjacentVertices.
     *  @return None
     *  @param vertex The adjacent vertex
     */
    void addAdjacent(Vertex *vertex)
    {
        adjacentVertices.push_back(vertex);
    }
};

/** A vector of vertices of the graph */
std::vector<Vertex *> vertices;

/**
 *  @brief Performs a topological sort on a graph.
 *  This function sorts a graph through the topological sort algorithm.
 *  @return None. Prints results of sort to screen.
 */
void topologicalSort()
{
    std::queue<Vertex *> q;
    Vertex *v, *w;

    for (int i = 0; i < vertices.size(); i++)
    {
        v = vertices[i];
        if (v->indegree == 0)
        {
            q.push(v);
        }
    }

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        std::cout << (v->name) << " ";
        for (int j = 0; j < (v->adjacentVertices.size()); j++)
        {
            w = v->adjacentVertices[j];
            if (--(w->indegree) == 0)
            {
                q.push(w);
            }
        }
    }

    std::cout << std::endl;
}

/**
 *  @brief Main method that reads in the input file.
 *  This main method reads in the input file and creates a graph of
 *  vertices and edges. It then calls topological() to sort the graph.
 *  @return None
 *  @param argc Number of command-line parameters passed
 *  @param argv Array of the command-line parameters passed
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Must supply the input file name as the one and only parameter." << std::endl;
        exit(1);
    }
    std::ifstream file(argv[1], std::ifstream::binary);
    if (!file.is_open())
    {
        std::cout << "Unable to open file '" << argv[1] << "'." << std::endl;
        exit(2);
    }

    while (file.good())
    {
        std::string s1, s2;
        bool s1present = false, s2present = false;
        int s1index = 0, s2index = 0;
        int counter = 0;
        file >> s1;
        file >> s2;

        if ((s1 == "0") && (s2 == "0"))
        {
            break;
        }

        counter = 0;
        for (Vertex *v : vertices)
        {
            if (v->name == s1)
            {
                s1index = counter;
                s1present = true;
                break;
            }
            counter++;
        }

        if (!s1present)
        {
            vertices.push_back(new Vertex(s1));
            s1index = vertices.size() - 1;
        }

        counter = 0;
        for (Vertex *v : vertices)
        {
            if (v->name == s2)
            {
                s2index = counter;
                s2present = true;
                break;
            }
            counter++;
        }

        if (!s2present)
        {
            vertices.push_back(new Vertex(s2));
            s2index = vertices.size() - 1;
        }

        vertices[s2index]->indegree += 1;
        vertices[s1index]->addAdjacent(vertices[s2index]);
    }

    topologicalSort();

    file.close();
}