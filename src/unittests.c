#include "unittests.h"

START_TEST(check_string_len_empty) {
    char empty[] = "";
    ck_assert(s21_strlen(empty)==strlen(empty));
}
END_TEST

Suite* my_functions_suite(void) {
    Suite* suite = suite_create("string");
    TCase* tc_core = tcase_create("strlen");
    tcase_add_test(tc_core, check_string_len_empty);
    // TCase* tc_core = tcase_create("strcat");
    // tcase_add_test(tc_core, check_string_cat1_empty);
    // tcase_add_test(tc_core, check_string_cat2_empty);
    suite_add_tcase(suite, tc_core);
    return suite;
}

int main(void) {
  int number_failed;
  Suite* suite = my_functions_suite();
  SRunner* runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NORMAL);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? 0 : 1;
}

