const int out[]  = {1, 2, 3, 4, 5, 6}; // Output pins in order
const int en[]   = {A1, A2, A3, A4, A5, A6}; // Manual switch input pins in order
const int enable = A7; // Override pin

int duration[] = {15, 15, 15, 15, 15, 15}; // Short circuit duration in ms in order
int period[] = {15, 15, 15, 15, 15, 15}; // Short circuit period in min in order

class My_cell {
  public:
    bool get_state();
    int set_fc(const int pin);
    void run(const bool pause);
    int set_period(const int period);
    int set_duration(const int duration);
    int set_switch(const int en);
  protected:
    bool set(bool state);
  private:
    bool my_state;
    int my_fc;
    int my_switch;
    int period;
    int duration;
    int time_last;
};

My_cell   FC[6];

void setup() {
  // put your setup code here, to run once:
  for (int i = 0 ; i = sizeof(FC) ; i++) {
    FC[i].set_fc(out[i]);
    FC[i].set_duration(duration[i]);
    FC[i].set_period(period[i]);
    FC[i].set_switch(en[i]);
  }
  for (int i = 0 ; i = sizeof(en) ; i++) {
    pinMode(en[i], INPUT_PULLUP);
  }
  pinMode(enable, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0 ; i = sizeof(FC) ; i++) {
    FC[i].run(digitalRead(enable));
  }
}

void My_cell::run(const bool pause) {
  if (My_cell::my_state == true) {
    if ((millis() - My_cell::time_last) >= My_cell::duration) {
      My_cell::my_state = false;
      My_cell::time_last = millis();
    }
  }
  else if (My_cell::my_state == false) {
    if ((millis() - My_cell::time_last) >= My_cell::period) {
      My_cell::my_state = true;
      My_cell::time_last = millis();
    }
  }
  
  if (pause) {
    My_cell::set(false);
  }
  else {
    My_cell::set(My_cell::my_state);
  }
  return;
}

bool My_cell::set(bool state) {
  if (digitalRead(My_cell::my_switch)) state = false;
  digitalWrite(My_cell::my_switch, state);
  return state;
}

int My_cell::set_duration(const int duration) {
  My_cell::duration = duration;
  return My_cell::duration;
}

int My_cell::set_period(const int period) {
  My_cell::period = period;
  return My_cell::period;
}

int My_cell::set_switch(const int en) {
  My_cell::my_switch = en;
  return My_cell::my_switch;
}

int My_cell::set_fc(const int pin) {
  pinMode(pin, OUTPUT);
  My_cell::my_fc = pin;
  return My_cell::my_fc;
}
