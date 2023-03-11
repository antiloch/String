#include "test_me.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {
      test_memchr(),  test_memcmp(),   test_memcpy(),   test_memmove(),
      test_memset(),  test_strcat(),   test_strncat(),  test_strchr(),
      test_strcmp(),  test_strncmp(),  test_strcpy(),   test_strncpy(),
      test_strcspn(), test_strerror(), test_strlen(),   test_strpbrk(),
      test_strrchr(), test_strspn(),   test_strstr(),   test_strtok(),
      test_sprintf(), test_to_upper(), test_to_lower(), test_insert(),
      test_trim(),    s21_NULL};

  for (int i = 0; s21_string_test[i] != s21_NULL; i++) {
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    int fail = srunner_ntests_failed(sr);
    if (fail > 0)
      printf("\033[1;41m FAILED: %d \033[0m\n", fail);
    else
      printf("\033[1;42m NO FAILS \033[0m\n");

    failed += fail;
    fail = 0;
    srunner_free(sr);
  }
  if (failed > 0)
    printf("\n\033[1;41m FAILED: %d \033[0m\n", failed);
  else
    printf("\n\033[1;42m ALL TESTS NO FAILS \033[0m\n");

  return failed == 0 ? 0 : 1;
}