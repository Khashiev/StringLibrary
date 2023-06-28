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
  char dest[32], src[32];

  strcpy(dest, "");
  strcpy(src, "");
  ck_assert_str_eq(s21_strncat(dest, src, 0), strncat(dest, src, 0));

  strcpy(dest, "Example");
  strcpy(src, "");
  ck_assert_str_eq(s21_strncat(dest, src, 0), strncat(dest, src, 0));

  strcpy(dest, "");
  strcpy(src, "bla");
  ck_assert_str_eq(s21_strncat(dest, src, 0), strncat(dest, src, 0));

  strcpy(dest, "Example");
  strcpy(src, "bla");
  ck_assert_str_eq(s21_strncat(dest, src, 2), strncat(dest, src, 2));

  strcpy(src, "Example");
  strcpy(dest, "bla");
  ck_assert_str_eq(s21_strncat(dest, src, 8), strncat(dest, src, 8));
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
