#include "test_me.h"

START_TEST(strerror_1) {
  for (int i = 1; i < 150; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(strerror_2) {
  int n = -1;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

START_TEST(strerror_3) {
  int n = 0;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

START_TEST(strerror_4) {
  int num_3 = 2147483647;
  ck_assert_str_eq(strerror(num_3), s21_strerror(num_3));
}
END_TEST

// START_TEST(strerror_5) {
//   int num_4 = -2147483648;
//   ck_assert_str_eq(strerror(num_4), s21_strerror(num_4));
// }
// END_TEST

END_TEST
Suite *test_strerror(void) {
  Suite *s = suite_create("\033[42m  S21_STRERROR  \033[0m");
  TCase *tc = tcase_create("strerror_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strerror_2);
  tcase_add_test(tc, strerror_3);
  tcase_add_test(tc, strerror_4);
  // tcase_add_test(tc, strerror_5);

  suite_add_tcase(s, tc);
  return s;
}