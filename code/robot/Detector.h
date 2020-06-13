class Detector
{
    private:
        int pin_;
    public:
        Detector(int pin) {
            this->pin_ = pin;
            pinMode(this-pin_, INPUT_PULLUP);
        }
        inline bool check() {
            if (digitalRead(this->pin_) == HIGH)
                return true;
            else 
                return false;
        }
};
