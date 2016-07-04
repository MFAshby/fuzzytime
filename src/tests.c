#include <pebble.h>
#include "tests.h"
#include "main.h"
#include "fuzz.h"


void assert(bool b, const char* desc) {
  if (!b) APP_LOG(APP_LOG_LEVEL_ERROR, "FAILED ASSERT %s" , desc);
}

void assert_equal_strings(char* s1, char* s2) {
  uint64_t len1 = strlen(s1);
  char buf[500];
  snprintf(buf, 500, "[%s] not equal to [%s]", s1, s2);
  assert(len1 == strlen(s2) && strncmp(s1, s2, len1) == 0, buf);
}


void run_tests() {
  char buf[MAX_TIME_LEN];
  fuzzy_time(buf, MAX_TIME_LEN, 0, 0);
  assert_equal_strings(buf, "twelve 'o' clock");
  
  fuzzy_time(buf, MAX_TIME_LEN, 0, 1);
  assert_equal_strings(buf, "one 'o' clock");
  
  fuzzy_time(buf, MAX_TIME_LEN, 5, 1);
  assert_equal_strings(buf, "five past one");
  
  fuzzy_time(buf, MAX_TIME_LEN, 55, 1);
  assert_equal_strings(buf, "five to two");
  
  fuzzy_time(buf, MAX_TIME_LEN, 30, 1);
  assert_equal_strings(buf, "half past one");
  
  fuzzy_time(buf, MAX_TIME_LEN, 59, 1);
  assert_equal_strings(buf, "two 'o' clock");
  
  fuzzy_time(buf, MAX_TIME_LEN, 0, 2);
  assert_equal_strings(buf, "two 'o' clock");
  
  fuzzy_time(buf, MAX_TIME_LEN, 2, 2);
  assert_equal_strings(buf, "five past two");
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Tests complete");
}