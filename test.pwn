#define RUN_TESTS

#include <a_samp>
#include <YSI\y_testing>

#include "../../POKER_CHECKER.inc"

main() {
    //
}

Test:RunTest() {
    new ret = MyFunction();
    printf("ret: %d", ret);
    ASSERT(ret == 0);
}
