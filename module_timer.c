#include "assets.h"

int compt_sec(Montre *clock){
  return clock->h*3600+clock->m*60+clock->s;
}

void reinject_clock(Montre *clock, int sec){
  int h, m;
  h = sec/3600;
  sec -= h*3600;
  m = sec/60;
  sec -= m*60;
  clock->h = h;
  clock->m = m;
  clock->s = sec;
}

void set_local_time(Montre *clock){
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
  clock->h = local->tm_hour;
  clock->m = local->tm_min;
  clock->s = local->tm_sec;
}

void set_clock(Montre *clock){
  clock->h = 0;
  clock->m = 0;
  clock->s = 0;
}

void update_time(Montre *clock1, Montre *clock2, Montre clock_init){
  Montre local;
  set_local_time(&local);
  reinject_clock(clock1, compt_sec(&local)-(compt_sec(&clock_init)+compt_sec(clock2)));
}
