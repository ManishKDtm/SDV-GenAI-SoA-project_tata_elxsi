#include <cstdint>
#include <array>
#include <cstdio>

namespace TirePressureService
{
    class ITirePressurePredictor
    {
    public:
        virtual void predict(const std::array<float, 4>& temperatures,
                             const std::array<uint16_t, 4>& loads,
                             std::array<float, 4>& predictedPressures) const = 0;
    };
}

class TirePressurePredictorImpl : public TirePressureService::ITirePressurePredictor
{
public:
    void predict(const std::array<float, 4>& temperatures,
                 const std::array<uint16_t, 4>& loads,
                 std::array<float, 4>& predictedPressures) const override
    {
        for (std::size_t i = 0; i < 4; ++i)
        {
            const float basePressure = 200.0f; // kPa
            const float tempFactor = -0.5f * temperatures[i];
            const float loadFactor = 0.01f * static_cast<float>(loads[i]);
            predictedPressures[i] = basePressure + tempFactor + loadFactor;
        }
    }
};

int main()
{
    std::array<float, 4> temperatures = {20.0f, 25.0f, 30.0f, 15.0f};
    std::array<uint16_t, 4> loads = {2000, 2500, 3000, 1500};
    std::array<float, 4> predictedPressures = {0.0f, 0.0f, 0.0f, 0.0f};

    TirePressurePredictorImpl concretePredictor;
    const TirePressureService::ITirePressurePredictor* predictor = &concretePredictor;

    predictor->predict(temperatures, loads, predictedPressures);

    for (std::size_t i = 0; i < 4; ++i)
    {
        std::printf("Tire %zu predicted pressure: %.2f kPa\n", i + 1, predictedPressures[i]);
    }

    return 0;
}