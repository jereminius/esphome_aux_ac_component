#pragma once

#include "aux_ac.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace aux_ac {

// ESPHome changed Action<Ts...>::play signature in 2025.11
// - <= 2025.10: virtual void play(Ts... x) = 0;
// - >= 2025.11: virtual void play(const Ts&... x) = 0;
#if ESPHOME_VERSION_CODE >= VERSION_CODE(2025, 11, 0)
#define AUXAC_PLAY_SIG void play(const Ts &...x) override
#else
#define AUXAC_PLAY_SIG void play(Ts... x) override
#endif

// **************************************** DISPLAY ACTIONS ****************************************
template <typename... Ts>
class AirConDisplayOffAction : public Action<Ts...> {
 public:
  explicit AirConDisplayOffAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->displayOffSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConDisplayOnAction : public Action<Ts...> {
 public:
  explicit AirConDisplayOnAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->displayOnSequence(); }

 protected:
  AirCon *ac_;
};

// **************************************** VERTICAL LOUVER ACTIONS ****************************************
template <typename... Ts>
class AirConVLouverSwingAction : public Action<Ts...> {
 public:
  explicit AirConVLouverSwingAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverSwingSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverStopAction : public Action<Ts...> {
 public:
  explicit AirConVLouverStopAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverStopSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverTopAction : public Action<Ts...> {
 public:
  explicit AirConVLouverTopAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverTopSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverMiddleAboveAction : public Action<Ts...> {
 public:
  explicit AirConVLouverMiddleAboveAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverMiddleAboveSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverMiddleAction : public Action<Ts...> {
 public:
  explicit AirConVLouverMiddleAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverMiddleSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverMiddleBelowAction : public Action<Ts...> {
 public:
  explicit AirConVLouverMiddleBelowAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverMiddleBelowSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverBottomAction : public Action<Ts...> {
 public:
  explicit AirConVLouverBottomAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->setVLouverBottomSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConVLouverSetAction : public Action<Ts...> {
 public:
  TEMPLATABLE_VALUE(uint8_t, value);

  explicit AirConVLouverSetAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG {
    vlpos_ = this->value_.value(x...);
    this->ac_->setVLouverFrontendSequence((ac_vlouver_frontend) vlpos_);
  }

 protected:
  AirCon *ac_;
  uint8_t vlpos_{0};
};

// **************************************** SEND TEST PACKET ACTION ****************************************
template <typename... Ts>
class AirConSendTestPacketAction : public Action<Ts...> {
 public:
  explicit AirConSendTestPacketAction(AirCon *ac) : ac_(ac) {}

  void set_data_template(std::function<std::vector<uint8_t>(Ts...)> func) {
    this->data_func_ = func;
    this->static_ = false;
  }
  void set_data_static(const std::vector<uint8_t> &data) {
    this->data_static_ = data;
    this->static_ = true;
  }

  AUXAC_PLAY_SIG {
    if (this->static_) {
      this->ac_->sendTestPacket(this->data_static_);
    } else {
      auto val = this->data_func_(x...);
      this->ac_->sendTestPacket(val);
    }
  }

 protected:
  AirCon *ac_;
  bool static_{false};
  std::function<std::vector<uint8_t>(Ts...)> data_func_{};
  std::vector<uint8_t> data_static_{};
};

// **************************************** POWER LIMITATION ACTIONS ****************************************
template <typename... Ts>
class AirConPowerLimitationOffAction : public Action<Ts...> {
 public:
  explicit AirConPowerLimitationOffAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG { this->ac_->powerLimitationOffSequence(); }

 protected:
  AirCon *ac_;
};

template <typename... Ts>
class AirConPowerLimitationOnAction : public Action<Ts...> {
 public:
  TEMPLATABLE_VALUE(uint8_t, value);

  explicit AirConPowerLimitationOnAction(AirCon *ac) : ac_(ac) {}

  AUXAC_PLAY_SIG {
    this->pwr_lim_ = this->value_.value(x...);
    this->ac_->powerLimitationOnSequence(this->pwr_lim_);
  }

 protected:
  AirCon *ac_;
  uint8_t pwr_lim_{0};
};

#undef AUXAC_PLAY_SIG

}  // namespace aux_ac
}  // namespace esphome

