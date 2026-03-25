#pragma once
#include <cstdint>
#include <array>

class IBatterySoCPredictor
{
public:
    virtual ~IBatterySoCPredictor() = default;
    virtual void Init() = 0;
    virtual std::uint16_t PredictSoC(const std::array<std::uint16_t, 3>& parameters) = 0;
};

class BatterySoCPredictor : public IBatterySoCPredictor
{
public:
    BatterySoCPredictor();
    void Init() override;
    std::uint16_t PredictSoC(const std::array<std::uint16_t, 3>& parameters) override;
private:
    std::array<std::int32_t, 3> coefficients_;
    std::int32_t bias_;
};

BatterySoCPredictor::BatterySoCPredictor()
    : coefficients_{0}, bias_(0)
{
}

void BatterySoCPredictor::Init()
{
    coefficients_[0] = 50;
    coefficients_[1] = 25;
    coefficients_[2] = 10;
    bias_ = 5;
}

std::uint16_t BatterySoCPredictor::PredictSoC(const std::array<std::uint16_t, 3>& parameters)
{
    std::int32_t sum = bias_;
    for (std::uint32_t i = 0; i < 3; ++i)
    {
        sum += static_cast<std::int32_t>(parameters[i]) * coefficients_[i];
    }
    if (sum < 0)
    {
        sum = 0;
    }
    if (sum > 10000)
    {
        sum = 10000;
    }
    return static_cast<std::uint16_t>(sum / 100);
}

#include <array>
#include <cstdio>

int main()
{
    BatterySoCPredictor predictor;
    predictor.Init();
    std::array<std::uint16_t, 3> params{2000, 3500, 1800};
    std::uint16_t soc = predictor.PredictSoC(params);
    std::printf("Predicted SoC: %u%%\n", static_cast<unsigned>(soc));
    return 0;
}