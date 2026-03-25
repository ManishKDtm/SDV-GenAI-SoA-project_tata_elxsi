#include <cstdint>
#include <iostream>

class MotorFailurePredictorService
{
public:
    virtual bool predictFailure(uint16_t temperature, uint16_t vibration, uint16_t current) = 0;
    virtual ~MotorFailurePredictorService() {}
};

class SimpleMotorFailurePredictor : public MotorFailurePredictorService
{
public:
    bool predictFailure(uint16_t temperature, uint16_t vibration, uint16_t current) override;
};

bool SimpleMotorFailurePredictor::predictFailure(uint16_t temperature, uint16_t vibration, uint16_t current)
{
    const uint16_t tempThreshold = 80U;
    const uint16_t vibThreshold = 60U;
    const uint16_t currThreshold = 200U;
    if (temperature > tempThreshold) return true;
    if (vibration > vibThreshold) return true;
    if (current > currThreshold) return true;
    return false;
}

int main()
{
    SimpleMotorFailurePredictor predictor;
    bool result = predictor.predictFailure(85U, 50U, 150U);
    std::cout << "Failure predicted: " << (result ? 1 : 0) << std::endl;
    return 0;
}