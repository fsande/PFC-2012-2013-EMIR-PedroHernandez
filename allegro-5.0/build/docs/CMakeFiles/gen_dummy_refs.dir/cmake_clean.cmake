FILE(REMOVE_RECURSE
  "CMakeFiles/gen_dummy_refs"
  "dummy_refs"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/gen_dummy_refs.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
