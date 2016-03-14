#include <queue>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


using std::cout;
using std::endl;
using std::string;

enum class op_type
{
    none,
    match,
    substitution,
    indel1,
    indel2
};

constexpr int indel_first = -8;
constexpr int indel_after = -1;
constexpr int substitution = -3;
constexpr int match = 3;

struct node
{
    node() : score{}, op{}, previous(nullptr) {}
    node(int score_, op_type op_, node* previous_) : score{score_}, op{op_}, previous{previous_} {}
    int score;
    op_type op;
    node* previous;
};

class score_table
{
public:
    score_table() = delete;
    score_table(int m_, int n_) : m(m_), n(n_)
    {
        data.resize(m*n);
    }
    
    node& operator()(int x, int y) { return data[x + y*n]; }
    
    int score;
    op_type op;
    int m, n;
    std::vector<node> data;
};

class gene_comparison
{
public:
    gene_comparison(string gene1_, string gene2_) : gene1(gene1_), gene2(gene2_), score{0}
    {
        if (gene2.length() > gene1.length())
        {
            std::swap(gene2, gene1);
        }
    }

    gene_comparison() = delete;

    int solve()
    {
        score_table d(gene1.length() + 1, gene2.length() + 1);
        
        d(0, 0) = {0, op_type::none, nullptr};
        d(0, 1) = {indel_first, op_type::indel1, &d(0, 0)};
        for (int i = 2; i < d.m; ++i)
        {
            d(0, i) = {d(0, i-1).score + indel_after, op_type::indel1, &d(0, i-1)};
        }
        d(1, 0) = {indel_first, op_type::indel2, &d(0, 0)};
        for (int i = 2; i < d.n; ++i)
        {
            d(i, 0) = {d(i-1, 0).score + indel_after, op_type::indel2, &d(i-1, 0)};
        }
        
        cout << std::setw(4) << std::setfill(' ') << ' ' << std::setw(4) << ' ';
        for (auto c : gene1)
        {
            cout << std::setw(4) << c;
        }
        cout << endl << std::setw(4) << ' ';
        for (int i = 0; i < d.m; ++i)
        {
            cout << std::setw(4) << d(0,i).score;
        }
        cout << endl;
        
        for (int i = 1; i < d.n; ++i)
        {
            cout << std::setw(4) << gene2[i - 1] << std::setw(4) << d(i,0).score;
            for (int j = 1; j < d.m; ++j)
            {
                int match_score{};
                if (gene1.at(j-1) == gene2.at(i-1))
                {
                    match_score = d(i-1, j-1).score + match;
                }
                else
                {
                    match_score = d(i-1, j-1).score + substitution;
                }
                auto indel1 = d(i-1, j).score + (d(i-1, j).op == op_type::indel1 ? indel_after : indel_first);
                auto indel2 = d(i, j-1).score + (d(i, j-1).op == op_type::indel2 ? indel_after : indel_first);
                if (match_score > indel1 && match_score > indel2)
                {
                    d(i,j) = {match_score, (gene1.at(j-1) == gene2.at(i-1) ? op_type::match : op_type::substitution), &d(i-1,j-1)};
                }
                else
                {
                    if (indel1 > indel2)
                    {
                        d(i,j) = {indel1, op_type::indel1, &d(i-1,j)};
                    }
                    else
                    {
                        d(i,j) = {indel2, op_type::indel2, &d(i,j-1)};
                    }
                }
                std::cout << std::setw(4) << (score = d(i,j).score);
            }
            
            std::cout << std::endl;
        }
        
        node* n = &d.data.back();
        
        string s1, s2;
        auto g1 = gene1.rbegin();
        auto g2 = gene2.rbegin();
        while (n)
        {
            switch(n->op)
            {
                case op_type::match:
                    cout << "match" << endl;
                    s1.insert(s1.begin(), *g1);
                    s2.insert(s2.begin(), *g2);
                    g1++; g2++;
                    break;
                case op_type::substitution:
                    cout << "sub" << endl;
                    s1.insert(s1.begin(), *g1);
                    s2.insert(s2.begin(), *g2);
                    g1++; g2++;
                    break;
                case op_type::indel2:
                    cout << "indel2" << endl;
                    s1.insert(s1.begin(), *g1);
                    s2.insert(s2.begin(), '-');
                    g1++;
                    break;
                case op_type::indel1:
                    cout << "indel1" << endl;
                    s1.insert(s1.begin(), '-');
                    s2.insert(s2.begin(), *g2);
                    g2++;
                    break;
            }
            n = n->previous;
        }
        
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;
        
        return d.data.back().score;
    }

private:
    string gene1;
    string gene2;
    int score;
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
        std::cout << comparison.solve() << std::endl;
    }

    return 0;
}
