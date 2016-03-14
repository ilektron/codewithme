#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

using coordinate = std::pair<int, int>;

coordinate out_of_bounds{-1, -1};
double distance(coordinate c1, coordinate c2)
{
    return sqrt(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2));
}

struct node
{
    node() = delete;

    node (coordinate xy_, coordinate prev_xy_, double distance_, int steps_) : xy(xy_), prev_xy(prev_xy_), distance(distance_), steps(steps_)
    {
    }

    bool operator<(const node& other) const
    {

        return (distance + steps > other.distance + other.steps);
    }

    coordinate xy;
    coordinate prev_xy;
    double distance;
    int steps;
};

class labyrinth
{
public:
    labyrinth(ifstream& input)
    {
        string line;
        while (getline(input, line))
        {
            if (line.length() > 0)
            {
                dimensions.first = line.length();
                ++dimensions.second;
                data += line;
            }
        }
    }

    labyrinth() = delete;

    bool solve()
    {
        // Find the entry point
        auto start = coordinate(data.find(' '), 0);
        auto end = coordinate(data.rfind(' ') % dimensions.first, dimensions.second - 1);

        open_nodes.emplace(start, out_of_bounds, distance(start, end), 1);
        mark_visited(start, 'S');

        while (!open_nodes.empty() && open_nodes.top().xy != end)
        {
            // push all the neighbors
            auto current_node = open_nodes.top();
            open_nodes.pop();
            visit_node(current_node, end);
        }

        trace_back(get_pos(start), get_pos(end));

        // clean up
        for (auto& c : data)
        {
            if (c != ' ' && c != '*' && c != '+')
            {
                c = ' ';
            }
        }

        return true;
    }

    friend ostream& operator<<(ostream& os, const labyrinth& labyrinth_)
    {
        for (auto itr = labyrinth_.data.begin(); itr != labyrinth_.data.end(); itr += labyrinth_.dimensions.first)
        {
            os << string(itr, itr + labyrinth_.dimensions.first) << endl;
        }

        return os;
    }

protected:

    string::iterator get_pos(coordinate coord) { return get_pos(coord.first, coord.second); }
    string::iterator get_pos(int x, int y)
    {
        return data.begin() + x + y * dimensions.second;
    }

    bool is_open(coordinate coord) { return is_open(coord.first, coord.second); }
    bool is_open(int x, int y)
    {
        auto pos = get_pos(x, y);
        return *pos == ' ';
    }

    void mark_visited(coordinate coord, char c) { mark_visited(coord.first, coord.second, c); }
    void mark_visited(int x, int y, char c)
    {
        auto pos = get_pos(x, y);
        *pos = c;
    }

    void visit_node(node& n, coordinate end)
    {
        auto xy = n.xy;
        auto next_coord = coordinate(xy.first, xy.second - 1);
        if (next_coord.second > 0 && is_open(next_coord))
        {
            mark_visited(next_coord, 'u');
            open_nodes.emplace(next_coord, xy, distance(next_coord, end), n.steps + 1);
        }
        next_coord = coordinate(xy.first, xy.second + 1);
        if (is_open(next_coord))
        {
            mark_visited(next_coord, 'd');
            open_nodes.emplace(next_coord, xy, distance(next_coord, end), n.steps + 1);
        }
        next_coord = coordinate(xy.first - 1, xy.second);
        if (is_open(next_coord))
        {
            mark_visited(next_coord, 'l');
            open_nodes.emplace(next_coord, xy, distance(next_coord, end), n.steps + 1);
        }
        next_coord = coordinate(xy.first + 1, xy.second);
        if (is_open(next_coord))
        {
            mark_visited(next_coord, 'r');
            open_nodes.emplace(next_coord, xy, distance(next_coord, end), n.steps + 1);
        }
    }

    void trace_back(string::iterator start, string::iterator end)
    {
        for (auto prev = end; start != end; *prev = '+', prev = end)
        {
            switch (*end)
            {
                case 'u': end += dimensions.first; break;
                case 'd': end -= dimensions.first; break;
                case 'l': end += 1; break;
                case 'r': end -= 1; break;
            }
        }
        *start = '+';
    }

private:
    string data;
    coordinate dimensions;
    priority_queue<node> open_nodes;
};

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    ifstream input(argv[1]);

    labyrinth lab(input);

    lab.solve();

    cout << lab;

    // Load the map

    return 0;
}