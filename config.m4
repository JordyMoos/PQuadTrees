
PHP_ARG_ENABLE(PQuadTrees,
    [Whether to enable PQuadTrees extension],
    [  --enable-pquadtrees     Enable PQuadTrees extension support])

if test $PHP_PQUADTREES != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(PQUADTREES_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, PQUADTREES_SHARED_LIBADD)
    PHP_NEW_EXTENSION(PQuadTrees, main.cpp point.cpp box.cpp, $ext_shared)
fi
