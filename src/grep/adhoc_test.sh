./s21_grep -vi fprintf dummy.c > my_grep
grep -vi fprintf dummy.c > unx_grep
echo "$(diff my_grep unx_grep)"
