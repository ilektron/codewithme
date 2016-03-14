#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::pair;
using std::string;

using coordinate = std::pair<string::iterator, string::iterator>;

enum class op_type
{
    none,
    match,
    mismatch,
    indel1,
    indel2
};

struct node
{
    node() = delete;

    node (coordinate coord_, int score_, op_type op_, double distance_) : coord(coord_), score(score_), op(op_), distance(distance_)
    {
    }

    bool operator<(const node& other) const
    {
        return (score) < (other.score);
    }

    coordinate coord;
    int score;
    op_type op;
    double distance;
};

class gene_comparison
{
public:
    gene_comparison(string gene1_, string gene2_) : gene1(gene1_), gene2(gene2_), score{} {}

    gene_comparison() = delete;

    int solve()
    {
        // Find the entry point
        coordinate start = coordinate(gene1.begin(), gene2.begin());
        coordinate end = coordinate(gene1.end(), gene2.end());

        open_nodes.emplace(start, 0, op_type::none, std::distance(start.first, end.first) + std::distance(start.second, end.second));

        while (!open_nodes.empty() && open_nodes.top().coord != end)
        {
            // push all the neighbors
            node current_node = open_nodes.top();
            open_nodes.pop();
            visit_node(current_node, end);
        }

        if (!open_nodes.empty())
        {
            score = open_nodes.top().score;
            cout << score << endl;
        }

        return score;
    }

protected:

    void visit_node(node& n, coordinate end)
    {
        coordinate& coord = n.coord;
        // Match +3
        if (coord.first != end.second
            && coord.second != end.second
            && *coord.first == *coord.second)
        {
            open_nodes.emplace(coordinate(coord.first + 1, coord.second + 1), n.score + 3, op_type::match, std::distance(coord.first + 1, end.first) + std::distance(coord.second + 1, end.second));
        }

        // Mismatch -3
        if (coord.first != end.second
            && coord.second != end.second
            && *coord.first != *coord.second)
        {
            open_nodes.emplace(coordinate(coord.first + 1, coord.second + 1), n.score - 3, op_type::mismatch, std::distance(coord.first + 1, end.first) + std::distance(coord.second + 1, end.second));
        }


        // Indel 1
        if (coord.first != end.first)
        {
            open_nodes.emplace(coordinate(coord.first + 1, coord.second), n.score + (n.op == op_type::indel1 ? -1 : -8), op_type::indel1, std::distance(coord.first + 1, end.first) + std::distance(coord.second, end.second));
        }

        // Indel 2
        if (coord.second != end.second)
        {
            open_nodes.emplace(coordinate(coord.first, coord.second + 1), n.score + (n.op == op_type::indel2 ? -1 : -8), op_type::indel2, std::distance(coord.first, end.first) + std::distance(coord.second + 1, end.second));
        }
    }

private:
    string gene1;
    string gene2;
    int score;
    std::priority_queue<node> open_nodes;
};

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    string gene1, gene2, delim;
    while (input >> gene1 >> delim >> gene2 && delim == "|")
    {
        gene_comparison comparison(gene1, gene2);
        comparison.solve();
    }

    return 0;
}