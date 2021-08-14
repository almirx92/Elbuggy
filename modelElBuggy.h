#ifndef MODELELBUGGY_H
#define MODELELBUGGY_H

struct  modelElBuggy {

    bool ubrzanjeStartBtn = false ;
    bool ubrzanjeStopBtn = false;
    bool kocenjeStartBtn = false;
    bool kocenjeStopBtn = false;
    bool smjerNaprijedBtn = false;
    bool smjerNazadBtn = false;
    bool onBtn = false;
    bool offBtn = false;

    float dialUbrzanje = 0;
    float dialKocenje = 0;

    void  setModelElBuggyParameters( bool ubrzanjeStartValue, bool ubrzanjeStopValue, bool kocenjeStartValue, bool kocenjeStopValue, bool smjerNaprijedValue, bool smjerNazadValue,bool onValue,bool offValue, float dialUbrzanjeValue ,float dialKocenjeValue){
      ubrzanjeStartBtn = ubrzanjeStartValue;
      ubrzanjeStopBtn = ubrzanjeStopValue;
      kocenjeStartBtn = kocenjeStartValue;
      kocenjeStopBtn = kocenjeStopValue;
      smjerNaprijedBtn = smjerNaprijedValue;
      smjerNazadBtn = smjerNazadValue;
      onBtn = onValue;
      offBtn = offValue;
      dialUbrzanje = dialUbrzanjeValue;
      dialKocenje = dialKocenjeValue;
    }
};

#endif // MODELELBUGGY_H
