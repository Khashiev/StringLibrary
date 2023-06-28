#include "unittests.h"

START_TEST(s21_memchr_test) {
  ck_assert_ptr_eq(s21_memchr("", '\0', 0), memchr("", '\0', 0));
  ck_assert_ptr_eq(s21_memchr("Example", '\0', 5), memchr("Example", '\0', 5));
  ck_assert_ptr_eq(s21_memchr("Example", 'E', 8), memchr("Example", 'E', 8));
  ck_assert_ptr_eq(s21_memchr("Example", 'e', 8), memchr("Example", 'e', 8));
  ck_assert_ptr_eq(s21_memchr("Example", 'm', 8), memchr("Example", 'm', 8));
}
END_TEST

START_TEST(s21_strchr_test) {
  ck_assert_pstr_eq(s21_strchr("Example", 'E'), strchr("Example", 'E'));
  ck_assert_pstr_eq(s21_strchr("Example", 'a'), strchr("Example", 'a'));
  ck_assert_pstr_eq(s21_strchr("Example", 'e'), strchr("Example", 'e'));
  ck_assert_pstr_eq(s21_strchr("Example", '3'), strchr("Example", '3'));
  ck_assert_pstr_eq(s21_strchr("Example", 'A'), strchr("Example", 'A'));
}
END_TEST

START_TEST(s21_strrchr_test) {
  ck_assert_pstr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
  ck_assert_pstr_eq(s21_strrchr("Example", '\0'), strrchr("Example", '\0'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'a'), strrchr("Example", 'a'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'k'), strrchr("Example", 'k'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'E'), strrchr("Example", 'E'));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  ck_assert_pstr_eq(s21_strpbrk("", ""), strpbrk("", ""));
  ck_assert_pstr_eq(s21_strpbrk("Example", ""), strpbrk("Example", ""));
  ck_assert_pstr_eq(s21_strpbrk("", "Example"), strpbrk("", "Example"));
  ck_assert_pstr_eq(s21_strpbrk("Example", "a"), strpbrk("Example", "a"));
  ck_assert_pstr_eq(s21_strpbrk("Example", "\0"), strpbrk("Example", "\0"));
}
END_TEST

START_TEST(s21_strstr_tets) {
  ck_assert_pstr_eq(s21_strstr("", ""), strstr("", ""));
  ck_assert_pstr_eq(s21_strstr("", "Example"), strstr("", "Example"));
  ck_assert_pstr_eq(s21_strstr("Example", ""), strstr("Example", ""));
  ck_assert_pstr_eq(s21_strstr("Example", "le"), strstr("Example", "le"));
  ck_assert_pstr_eq(s21_strstr("Example", "kj"), strstr("Example", "kj"));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -1; i < 135; i++) {
    char *err1 = s21_strerror(i);
    char *err2 = strerror(i);
    ck_assert_str_eq(err1, err2);
  }
}
END_TEST

START_TEST(s21_strncat_test) {
  char dest1[32], src1[32];
  strcpy(dest1, "");
  strcpy(src1, "");
  ck_assert_str_eq(s21_strncat(dest1, src1, 0), strncat(dest1, src1, 0));

  char dest2[32], src2[32];
  strcpy(dest2, "Example");
  strcpy(src2, "");
  ck_assert_str_eq(s21_strncat(dest2, src2, 0), strncat(dest2, src2, 0));

  char dest3[32], src3[32];
  strcpy(dest3, "");
  strcpy(src3, "bla");
  ck_assert_str_eq(s21_strncat(dest3, src3, 0), strncat(dest3, src3, 0));

  char dest4[32], src4[32];
  strcpy(dest4, "Example");
  strcpy(src4, "bla");
  ck_assert_str_eq(s21_strncat(dest4, src4, 2), strncat(dest4, src4, 2));

  char dest5[32], src5[32];
  strcpy(dest5, "Example");
  strcpy(src5, "bla");
  ck_assert_str_eq(s21_strncat(dest5, src5, 8), strncat(dest5, src5, 8));
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "Blabla.ba++F.oora_! tyigdyik==Sh.osa";
  char str2[] = "Blabla.ba++F.oora_! tyigdyik==Sh.osa";
  const char delims[] = ".";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

Suite *my_functions_suite(void) {
  Suite *suite = suite_create("string");
  TCase *tc_core = tcase_create("strlen");

  tcase_add_test(tc_core, s21_memchr_test);
  tcase_add_test(tc_core, s21_strchr_test);
  tcase_add_test(tc_core, s21_strrchr_test);
  tcase_add_test(tc_core, s21_strpbrk_test);
  tcase_add_test(tc_core, s21_strstr_tets);
  tcase_add_test(tc_core, s21_strerror_test);
  tcase_add_test(tc_core, s21_strncat_test);
  tcase_add_test(tc_core, s21_strtok_test);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = my_functions_suite();
  SRunner *runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? 0 : 1;
}
