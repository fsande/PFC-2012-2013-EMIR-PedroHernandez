FILE(REMOVE_RECURSE
  "CMakeFiles/check_consistency"
  "protos"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/check_consistency.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
