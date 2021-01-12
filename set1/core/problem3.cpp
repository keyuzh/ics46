#include <vector>
#include <random>


std::vector<unsigned int> countRandomFrequencies(
    unsigned int count,
    const std::vector<unsigned int>& weights)
    {
        // start random generator
        // we want a discrete distribution to count for weights
        std::random_device device;
        std::default_random_engine engine{device()};
        std::discrete_distribution<unsigned int> distribution(
            weights.begin(), weights.end());

        // initiate the vector contains result of random frequencies
        std::vector<unsigned int> result(weights.size(), 0);
        // generate random values
        for (unsigned int i = 0; i < count; i++)
        {
            result[distribution(engine)]++;
        }
        return result;
    }
