#pragma once
#include <array>
#include <cstdint>

class ISoCService
{
public:
    virtual ~ISoCService() = default;
    virtual float predictSoC(const std::array<float, 5u>& samples) = 0;
};

extern "C" ISoCService* createSoCService();


#include "ISoCService.hpp"

class SoCService : public ISoCService
{
public:
    float predictSoC(const std::array<float, 5u>& samples) override
    {
        float sum = 0.0f;
        for (std::size_t i = 0u; i < samples.size(); ++i)
        {
            sum += samples[i];
        }
        return sum / static_cast<float>(samples.size());
    }
};

extern "C" ISoCService* createSoCService()
{
    static SoCService instance;
    return &instance;
}


#include "ISoCService.hpp"
#include <array>
#include <iostream>

int main()
{
    ISoCService* socService = createSoCService();
    std::array<float, 5u> samples = { 80.0f, 82.0f, 78.0f, 81.0f, 79.0f };
    float soc = socService->predictSoC(samples);
    std::cout << "SoC: " << soc << "%\n";
    return 0;
}