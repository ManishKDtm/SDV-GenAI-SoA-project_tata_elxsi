#pragma once
#include <cstdint>
class ISpeedSensor {
public:
    virtual uint16_t GetSpeedKmPerHour() const = 0;
};

#pragma once
#include "SpeedSensorInterface.hpp"
class SpeedService : public ISpeedSensor {
public:
    SpeedService();
    void SetSpeed(uint16_t speed);
    uint16_t GetSpeedKmPerHour() const override;
private:
    uint16_t speed_;
};

#include "SpeedSensor.hpp"
SpeedService::SpeedService() : speed_(0) {}
void SpeedService::SetSpeed(uint16_t speed) { speed_ = speed; }
uint16_t SpeedService::GetSpeedKmPerHour() const { return speed_; }

#pragma once
#include <cstdint>
enum class LightType : uint8_t { Headlights, Backlights, LeftIndicator, RightIndicator };
class ILightingService {
public:
    virtual void SetAllOn() = 0;
    virtual void SetAllOff() = 0;
    virtual void FlashAll() = 0;
    virtual void Update() = 0;
    virtual bool GetState(LightType type) const = 0;
};

#pragma once
#include "LightingServiceInterface.hpp"
#include <array>
class LightingService : public ILightingService {
public:
    LightingService();
    void SetAllOn() override;
    void SetAllOff() override;
    void FlashAll() override;
    void Update() override;
    bool GetState(LightType type) const override;
private:
    std::array<bool, 4> states_;
    bool flashing_;
};

#include "LightingService.hpp"
LightingService::LightingService() : states_{false,false,false,false}, flashing_(false) {}
void LightingService::SetAllOn() { states_ = {true,true,true,true}; flashing_ = false; }
void LightingService::SetAllOff() { states_ = {false,false,false,false}; flashing_ = false; }
void LightingService::FlashAll() { flashing_ = true; }
void LightingService::Update() { if (flashing_) { for (auto& s : states_) { s = !s; } } }
bool LightingService::GetState(LightType type) const { return states_[static_cast<std::size_t>(type)]; }

#pragma once
#include "SpeedSensorInterface.hpp"
#include "LightingServiceInterface.hpp"
class SpeedMonitorService {
public:
    SpeedMonitorService(ISpeedSensor const* speedSensor, ILightingService* lightingService);
    void Update();
private:
    ISpeedSensor const* speedSensor_;
    ILightingService* lightingService_;
    bool flashingEnabled_;
};

#include "SpeedMonitorService.hpp"
SpeedMonitorService::SpeedMonitorService(ISpeedSensor const* speedSensor, ILightingService* lightingService)
    : speedSensor_(speedSensor), lightingService_(lightingService), flashingEnabled_(false) {}
void SpeedMonitorService::Update() {
    uint16_t speed = speedSensor_->GetSpeedKmPerHour();
    if (speed > 200U) {
        if (!flashingEnabled_) {
            lightingService_->FlashAll();
            flashingEnabled_ = true;
        }
        lightingService_->Update();
    } else {
        if (flashingEnabled_) {
            lightingService_->SetAllOff();
            flashingEnabled_ = false;
        }
    }
}

#include <iostream>
#include "SpeedSensor.hpp"
#include "LightingService.hpp"
#include "SpeedMonitorService.hpp"
int main() {
    SpeedService speedService;
    LightingService lightingService;
    SpeedMonitorService monitor(&speedService, &lightingService);
    speedService.SetSpeed(150);
    for (int i = 0; i < 5; ++i) monitor.Update();
    std::cout << "Below threshold: ";
    for (int i = 0; i < 4; ++i) std::cout << lightingService.GetState(static_cast<LightType>(i));
    std::cout << std::endl;
    speedService.SetSpeed(220);
    for (int i = 0; i < 5; ++i) monitor.Update();
    std::cout << "Above threshold: ";
    for (int i = 0; i < 4; ++i) std::cout << lightingService.GetState(static_cast<LightType>(i));
    std::cout << std::endl;
    speedService.SetSpeed(180);
    for (int i = 0; i < 5; ++i) monitor.Update();
    std::cout << "After reduction: ";
    for (int i = 0; i < 4; ++i) std::cout << lightingService.GetState(static_cast<LightType>(i));
    std::cout << std::endl;
    return 0;
}