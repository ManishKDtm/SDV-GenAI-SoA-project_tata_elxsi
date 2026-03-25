#include <array>
#include <cstdint>
#include <cstdio>

namespace AirQuality {

class IAQPredictor {
public:
    virtual void Predict(const std::array<uint16_t,3> & sensorValues, uint8_t & outQuality) const = 0;
    virtual ~IAQPredictor() {}
};

class IAlertService {
public:
    virtual void Alert(uint8_t quality) const = 0;
    virtual ~IAlertService() {}
};

}

class SimpleAQPredictor : public AirQuality::IAQPredictor {
public:
    void Predict(const std::array<uint16_t,3> & sensorValues, uint8_t & outQuality) const override {
        const uint32_t tempWeight = 1;
        const uint32_t humWeight = 1;
        const uint32_t co2Weight = 1;
        uint32_t sum = tempWeight * sensorValues[0] + humWeight * sensorValues[1] + co2Weight * sensorValues[2];
        if (sum > 10000u) sum = 10000u;
        outQuality = static_cast<uint8_t>(sum / 100u);
    }
};

class SimpleAlertService : public AirQuality::IAlertService {
public:
    void Alert(uint8_t quality) const override {
        if (quality > 70u) {
            std::printf("Alert: Poor air quality! Index: %u\n", quality);
        }
    }
};

int main(void) {
    SimpleAQPredictor predictor;
    SimpleAlertService alertService;
    std::array<uint16_t,3> sensorValues = {2500u, 4000u, 6000u};
    uint8_t quality = 0u;
    predictor.Predict(sensorValues, quality);
    alertService.Alert(quality);
    return 0;
}