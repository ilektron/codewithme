#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <memory>

enum class shape_type
{
    circle,
    square,
    triangle,
};

class shape
{
    public:
        shape(shape_type type_) : type{type_} {}
        shape_type get_type() { return type; }
        bool operator<(const shape& other) { return type < other.type; }

        virtual float get_data() = 0;
        
    private:
        shape_type type;
};

class circle : public shape
{
    public:
        circle(float r_) : shape{shape_type::circle}, r{r_} {}
        float get_data() override { return r; }
    private:
        float r;
};

class square : public shape
{
    public:
        square(float a_) : shape{shape_type::square}, a{a_} {}
        float get_data() override { return a; }
    private:
        float a;

};

class triangle : public shape
{
    public:
        triangle(float h_) : shape{shape_type::triangle}, h{h_} {}
        float get_data() override { return h; }
    private:
        float h;

};

void calc_total(const std::vector<std::unique_ptr<shape>>& data)
{
    float sum{};
    
    for (const auto& shape_ptr : data)
    {
        sum += shape_ptr->get_data();
    }
//     std::cout << "sum: " << sum << std::endl;
}

int main(int argc, const char* argv[])
{
    // Fill up an array of random shapes
    std::vector<std::unique_ptr<shape>> data;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> real_dist(0.1f,10.0f);
    std::uniform_int_distribution<int> shape_dist(1, 3);

    constexpr int num_shapes = 100000;
    for (int i = 0; i < num_shapes; i++)
    {
        switch (shape_dist(generator))
        {
            case 1:
                data.emplace_back(new circle(real_dist(generator)));
                break;
            case 2:
                data.emplace_back(new square(real_dist(generator)));
                break;
            case 3:
                data.emplace_back(new triangle(real_dist(generator)));
                break;
        }
    }

    // Calculate the average of each item and time it
    auto start = std::chrono::high_resolution_clock::now();
    calc_total(data);
    auto finish = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << "Baseline time: " << elapsed.count() << "us" << std::endl;
    
    constexpr int num_iterations = 100;
    long average_sorted{};
    long average_shuffled{};
    
    for (int i = 0; i < num_iterations; ++i)
    {
        // Sort the array, and repeat the calculation
        std::sort(data.begin(), data.end(), [](auto& lhs, auto& rhs){ return *lhs < *rhs;});
        start = std::chrono::high_resolution_clock::now();
        calc_total(data);
        finish = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        average_sorted += elapsed.count();
        
        // Shuffle the array, and repeat the calculation
        std::random_shuffle(data.begin(), data.end());
        start = std::chrono::high_resolution_clock::now();
        calc_total(data);
        finish = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        average_shuffled += elapsed.count();
    }
    
    std::cout << "Average sorted time: " << (average_sorted/num_iterations) << "us" << std::endl;
    std::cout << "Average shuffled time: " << (average_shuffled/num_iterations) << "us" << std::endl;
   
    return 0;
}
