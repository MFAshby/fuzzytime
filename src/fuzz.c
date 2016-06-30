#include <pebble.h>
#include "fuzz.h"

void fuzzy_time(char* buf, int max_len, int minutes, int hours) {
  static char* hour_descs[] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
  static char* diff_quantities[] = {" 'o' clock", "five", "ten", "quarter", "twenty", "twenty-five", "half"};
  // switch 3 minutes in advance
  minutes = minutes + 3;
  
  int hour_index = hours % 12;
  int diff_q_index = minutes / 5;
  char* descriptor;
  char* diff_quantity = diff_quantities[diff_q_index];
  char* postfix = "";
  
  if (diff_q_index == 0) {
    descriptor = "";
    postfix = diff_quantities[0];
    diff_quantity = "";
  }
  else {
    if (diff_q_index > 6) {
      hour_index = (hour_index + 1) % 12;
      diff_q_index = 12 - diff_q_index;
      descriptor = " to ";
    } else {
      descriptor = " past ";
    }
    diff_quantity = diff_quantities[diff_q_index];
  }
  
  char* hour_str = hour_descs[hour_index];
  snprintf(buf, max_len, "%s%s%s%s", diff_quantity, descriptor, hour_str, postfix);
}