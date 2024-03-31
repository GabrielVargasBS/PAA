#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

class Test {
public:
    int numberOfExecutions;
    vector<std::chrono::nanoseconds> duration;

    Test(int numberOfExecutions) {
        this->numberOfExecutions = numberOfExecutions;
    }

    void addDuration(std::chrono::_V2::system_clock::time_point start, std::chrono::_V2::system_clock::time_point stop) {
        std::chrono::nanoseconds dur = std::chrono::nanoseconds(stop - start);
        duration.push_back(dur);
    }
    
    void printExecutionTime(string test) {
        chrono::nanoseconds sum = chrono::nanoseconds::zero();

        for (const auto& dur : duration) {
            sum += dur;
        }

        auto average = sum / duration.size();

        auto minutes = duration_cast<chrono::minutes>(average);
        average -= minutes;
        auto seconds = duration_cast<chrono::seconds>(average);
        average -= seconds;
        auto milliseconds = duration_cast<chrono::milliseconds>(average);
        average -= milliseconds;
        auto microseconds = duration_cast<chrono::microseconds>(average);
        average -= microseconds;
        auto nanoseconds = duration_cast<chrono::nanoseconds>(average);

        std::cout << "[" << test << "]: " 
                  << "Tempo de execução: " << minutes.count() << " minutos, "
                  << seconds.count() << " segundos, "
                  << milliseconds.count() << " milissegundos, "
                  << microseconds.count() << " microssegundos, "
                  << nanoseconds.count() << " nanossegundos\n";

    }

};