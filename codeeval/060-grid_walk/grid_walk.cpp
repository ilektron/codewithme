#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>

constexpr int monkey_limit = 20;

class point
{
    public:

        point() = default;
        point(int x, int y) : x(x), y(y) {}

        bool is_monkeyable() const
        {
            int sum{};
            for (int _x{std::abs(x)}, _y{std::abs(y)}; (_x > 0 || _y > 0) && sum < monkey_limit; _x = _x / 10, _y = _y / 10)
            {
                sum += _x % 10 + _y % 10;
            }
            return sum < monkey_limit;
        }
        bool operator==(const point& p) const { return p.x == x && p.y == y; }

        int x;
        int y;
};

struct point_hash
{
    std::size_t operator()(const point& p) const
    {
        return p.x << 16 | p.y;
    }
};

void check_point(point p, std::vector<point>& search, std::unordered_set<point, point_hash>& visited)
{
    if (p.is_monkeyable() && visited.find(p) == visited.end())
    {
        visited.insert(p);
        search.push_back(p);
    }
}

int main(int, const char**)
{
    std::unordered_set<point, point_hash> visited = {{0,0}};
    std::vector<point> search = {{0,0}};

    while (!search.empty())
    {
        point p = search.back();
        search.pop_back();

        check_point(point{p.x, p.y + 1}, search, visited);
        check_point(point{p.x + 1, p.y}, search, visited);
        check_point(point{p.x, p.y - 1}, search, visited);
        check_point(point{p.x - 1, p.y}, search, visited);
    }
    std::cout << visited.size() << std::endl;
}
