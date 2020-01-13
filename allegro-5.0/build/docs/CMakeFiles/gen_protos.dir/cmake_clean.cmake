FILE(REMOVE_RECURSE
  "CMakeFiles/gen_protos"
  "protos"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/gen_protos.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
