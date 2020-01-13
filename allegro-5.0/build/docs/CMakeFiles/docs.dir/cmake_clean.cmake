FILE(REMOVE_RECURSE
  "CMakeFiles/docs"
  "html/changes-5.0.html"
  "texi/changes-5.0.texi"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/docs.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
