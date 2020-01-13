FILE(REMOVE_RECURSE
  "CMakeFiles/gen_tags"
  "tags"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/gen_tags.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
