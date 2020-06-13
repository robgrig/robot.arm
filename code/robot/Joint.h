class Joint
{
    private:
        int PUL_pin_;
        int DIR_pin_;
        int ENA_pin_;
        int step_cnt_;
        int motorDelayTime_;
        int detector_pin_;
    public:
        Joint(int PUL_pin, int DIR_pin, int ENA_pin, int motorDelayTime, int detector_pin) {
            this->PUL_pin_ = PUL_pin;
            this->DIR_pin_ = DIR_pin;
            this->ENA_pin_ = ENA_pin;
            this->motorDelayTime_ = motorDelayTime;
            this->detector_pin_ = detector_pin;

            pinMode (PUL_pin_, OUTPUT);
            pinMode (DIR_pin_, OUTPUT);
            //if (this->ENA_pin_ != -1) {
            pinMode (ENA_pin_, OUTPUT);
            digitalWrite(ENA_pin_,HIGH);
        //}
            // setup detector ending if available
            if (this->detector_pin_ != -1) {
              pinMode(this->detector_pin_, INPUT_PULLUP);
            }
          
        }
        void calibrate() {
          while(digitalRead(this->detector_pin_ ) == 0) {
            one_step_anticlockwise(400);
          }
        }
        void changeDirClockWise() {
            digitalWrite(this->DIR_pin_, 1);
        }

        void changeDirAntiClockWise() {
            digitalWrite(this->DIR_pin_, 0);
        }
        void one_step_clockwise() {
            this->changeDirClockWise();
            digitalWrite(this->PUL_pin_, HIGH);
            delayMicroseconds(this->motorDelayTime_); 
            digitalWrite(this->PUL_pin_, LOW);
            delayMicroseconds(this->motorDelayTime_); 
        }
        void one_step_anticlockwise() {
            this->changeDirAntiClockWise();
            digitalWrite(this->PUL_pin_, HIGH);
            delayMicroseconds(this->motorDelayTime_); 
            digitalWrite(this->PUL_pin_, LOW);
            delayMicroseconds(this->motorDelayTime_); 
        }
        void one_step_anticlockwise(int customDelayTime) {
            this->changeDirAntiClockWise();
            digitalWrite(this->PUL_pin_, HIGH);
            delayMicroseconds(customDelayTime); 
            digitalWrite(this->PUL_pin_, LOW);
            delayMicroseconds(customDelayTime); 
        }

        void n_stepClockWise(int steps) {
            this->changeDirClockWise();
            for (int i = 0; i < steps; i++) {
                digitalWrite(this->PUL_pin_, HIGH);
                delayMicroseconds(this->motorDelayTime_); 
                digitalWrite(this->PUL_pin_, LOW);
                delayMicroseconds(this->motorDelayTime_); 
            }
        }
        void n_stepAntiClockWise(int steps) {
            this->changeDirAntiClockWise();
            for (int i = 0; i < steps; i++) {
                digitalWrite(this->PUL_pin_, HIGH);
                delayMicroseconds(this->motorDelayTime_); 
                digitalWrite(this->PUL_pin_, LOW);
                delayMicroseconds(this->motorDelayTime_); 
            }
        }
};
