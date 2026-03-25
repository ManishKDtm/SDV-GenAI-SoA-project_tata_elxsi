#line 1 "TirePressurePredictor.hpp"
#pragma once

#include <array>
#include <cstdint>
#include <limits>

class ITirePressurePredictor
{
public:
    virtual void setRawPressures(const std::array<int16_t, 4> & pressures) = 0;
    virtual int16_t predictPressure(uint8_t tireIndex) const = 0;
    virtual ~ITirePressurePredictor() = default;
};

class TirePressurePredictor : public ITirePressurePredictor
{
private:
    std::array<int16_t, 4> rawPressures_;
public:
    TirePressurePredictor();
    void setRawPressures(const std::array<int16_t, 4> & pressures) override;
    int16_t predictPressure(uint8_t tireIndex) const override;
};

#line 1 "TirePressurePredictor.cpp"

#include "TirePressurePredictor.hpp"

TirePressurePredictor::TirePressurePredictor() : rawPressures_{0, 0, 0, 0} {}

void TirePressurePredictor::setRawPressures(const std::array<int16_t, 4> & pressures)
{
    rawPressures_ = pressures;
}

int16_t TirePressurePredictor::predictPressure(uint8_t tireIndex) const
{
    if (tireIndex >= 4U)
    {
        return 0;
    }
    const int16_t raw = rawPressures_[tireIndex];
    int32_t predicted = static_cast<int32_t>(raw) + 5;
    int32_t scaled = (predicted * 11) / 10;
    if (scaled > std::numeric_limits<int16_t>::max())
    {
        return std::numeric_limits<int16_t>::max();
    }
    if (scaled < std::numeric_limits<int16_t>::min())
    {
        return std::numeric_limits<int16_t>::min();
    }
    return static_cast<int16_t>(scaled);
}

#line 1 "main.cpp"

#include <iostream>
#include "TirePressurePredictor.hpp"

int main()
{
    TirePressurePredictor predictor;
    std::array<int16_t, 4> raw{200, 205, 198, 210};
    predictor.setRawPressures(raw);
    for (uint8_t i = 0; i < 4U; ++i)
    {
        int16_t predicted = predictor.predictPressure(i);
        std::cout << "Tire " << static_cast<int>(i) << " predicted pressure: " << predicted << std::endl;
    }
    return 0;
}