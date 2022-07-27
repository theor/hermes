//
// Created by theor on 2022-07-27.
//

#ifndef HERMES_UTILS_H
#define HERMES_UTILS_H

template<typename T>
T seq(T *sequence, size_t seq_len, float t, float duration, bool cycle = false) {
    // 0 - 1000
    // dur 500
    // t 0.5
    // x = 500
    size_t x = (size_t) (t * 1000);
    if (x < 0)
        x = 0;
    else {

        if (cycle)
            x = x % 1000;
        else if (x >= 1000)
            x = 999;
    }
    x = x * seq_len / 1000;
    return sequence[x];
}

struct Timer {
private:
    unsigned long _duration;
    unsigned long _cooldown;
    unsigned long _start;
    bool _inCooldown;
    bool _endedCooldown;
    uint8_t _cycleCount;
public:

    Timer() : _duration(0), _cooldown(0), _start(0), _inCooldown(false),
            _endedCooldown(true),
            _cycleCount(0){};
    uint8_t getCycleCount() const {
        return _cycleCount;
    }
    unsigned long getDuration() const {
        return _duration;
    }

    unsigned long getCooldown() const {
        return _cooldown;
    }

public:
    void setDuration(unsigned long duration) { _duration = duration; }

    void setCooldown(unsigned long cooldown) { _cooldown = cooldown; }
    bool endedCooldown() const {return _endedCooldown;}
    float cooldownProgress() const {
        if (_cooldown == 0)
            return 0;
        unsigned long m = millis();
        unsigned long d = m - _start;
        if(d < _duration)
            return 0;
        return fmin(1, (d - _duration) / (float)_cooldown);
    };

    bool update() {
        unsigned long m = millis();
        unsigned long d = m - _start;
//        Serial.println(String(d) + String(" dur ") + _duration);
        _endedCooldown = false;
        if (d < _duration)
            return false;
        if (!_inCooldown) {
//            Serial.println( String("    _start cooldown"));
            _inCooldown = true;
            return true;
        }
        if (d > _duration + _cooldown) {
//            Serial.println( String("        end cooldown"));
            _inCooldown = false;
            _endedCooldown = true;
            _cycleCount++;
            _start = m;
        }
        return false;
    }
};

#endif //HERMES_UTILS_H
