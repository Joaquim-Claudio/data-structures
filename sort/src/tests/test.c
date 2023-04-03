#include "unity.h"
#include "../modules/lib.h"

void setUp(){
}
void tearDown(){
}

void test_divisao() {
    TEST_ASSERT_EQUAL(31/64 , divisao(31, 64));
}

int main(){

    UNITY_BEGIN();
    RUN_TEST(test_divisao);
    return UNITY_END();
}