
PHP_ARG_ENABLE(PQuadTrees,
    [Whether to enable PQuadTrees extension],
    [ --enable-pquadtrees       Enable PQuadTrees extension support])

if test $PHP_PQUADTREES != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(PQUADTREES_SHARED_LIBADD)
    PHP_ADD_PIBRARY(stdc++, 1, PQUADTREES_SHARED_LIBADD)
    PHP_NEW_EXTENSION(PQuadTrees, main.cpp, $ext_shared)
fi