#include <stdio.h>
#include <string.h>

struct a_test1 {
    short a;
    int x;
    short b;
} table1[10];
struct a_test1 *p1, *q1;

struct a_test2 {
    short a;
    short b;
    int x;
} table2[10];
struct a_test2 *p2, *q2;

struct a_test3 {
    char c; // 1 byte
    // 1 byte padding
    short s; // 2 bytes
    int k; // 4 bytes
    long l; // 8 bytes
    float f; // 4 bytes
    // 4 bytes padding
    double d; // 8 bytes
    // `a_test3` size is 32 bytes
} table3[10];
struct a_test3 *p3, *q3;

struct a_test4 {
    // Optimization technique: put larger size elements first and smaller size at last
    double d; // 8 bytes
    long l; // 8 bytes
    float f; // 4 bytes
    int k; // 4 bytes
    short s; // 2 bytes
    char c; // 1 byte
    // 5 bytes padding
    // Variables above adds up to 27 bytes, so we need to add 5 bytes of padding to make it 32 bytes, because a_test4 has a alignment requirement of 8 bytes
    // `a_test4` size is 32 bytes
} table4[10];
struct a_test4 *p4, *q4;

char divider[100] = "----------------------------------------";
void print_divider(char *msg) {
    printf("\n%s %s %s\n", divider, msg, divider);
}

int main() {
    //# a_test1
    print_divider("a_test1");
    // Define/Declare structure a_test1 and its array container as:
    p1 = &table1[0];

    // a-Print the sizeof each member type in struct a_test1 (here short and int)
    printf("\na-Print the sizeof each member type in struct a_test1\n");
    printf("Size of `short a` is %d\n", sizeof(p1->a));
    printf("Size of `int x` is %d\n", sizeof(p1->x));
    printf("Size of `short b` is %d\n", sizeof(p1->b));

    // b-Print the size of table1[0] and then the sizeof the whole table1
    printf("\nb-Print the size of table1[0] and then the sizeof the whole table1\n");
    printf("Size of `table1[0]` is %d\n", sizeof(table1[0]));
    printf("Size of `table1` is %d\n", sizeof(table1));

    // c-Print the alignment and address of table1[0]
    printf("\nc-Print the alignment and address of table1[0]\n");
    printf("Alignment of table1[0] is %zu\n", _Alignof(table1[0]));  // not sure if this is correct

    // d-In a loop, print the aligned addresses of the previous and the current elements in table1 (starting with table1[1]), and then the difference between their addresses showing the length of the previous element in the array
    printf("\nd-Show the length of an element in the array\n");
    printf("Address of `table1[0]` is %p\n", &table1[0]);
    printf("Address of `table1[1]` is %p\n", &table1[1]);
    printf("Length of `table1[0]` is %d\n", (size_t)&table1[1] - (size_t)&table1[0]);

    //# a_test2
    print_divider("a_test2");
    // Apply the same instructions above (a-d) on the new a_test2 struct, //save the results in proper tables and describe about them in your report // your optimized structure will be compared with its initial format

    p2 = &table2[0];

    // a-Print the sizeof each member type in struct a_test2 (here short and int)
    printf("\na-Print the sizeof each member type in struct a_test2\n");
    printf("Size of `short a` is %d\n", sizeof(p2->a));
    printf("Size of `short b` is %d\n", sizeof(p2->b));
    printf("Size of `int x` is %d\n", sizeof(p2->x));

    // b-Print the size of table2[0] and then the sizeof the whole table2
    printf("\nb-Print the size of table2[0] and then the sizeof the whole table2\n");
    printf("Size of `table2[0]` is %d\n", sizeof(table2[0]));
    printf("Size of `table2` is %d\n", sizeof(table2));

    // c-Print the alignment and address of table2[0]
    printf("\nc-Print the alignment and address of table2[0]\n");
    printf("Alignment of table2[0] is %zu\n", _Alignof(table2[0]));  // not sure if this is correct

    // d-In a loop, print the aligned addresses of the previous and the current elements in table2 (starting with table2[1]), and then the difference between their addresses showing the length of the previous element in the array
    printf("\nd-Show the length of an element in the array\n");
    printf("Address of `table2[0]` is %p\n", &table2[0]);
    printf("Address of `table2[1]` is %p\n", &table2[1]);
    printf("Length of `table2[0]` is %d\n", (size_t)&table2[1] - (size_t)&table2[0]);


    //# a_test3
    print_divider("a_test3");
    p3 = &table3[0];

    // a-Print the sizeof each member type in struct a_test3 (here short and int)
    printf("\na-Print the sizeof each member type in struct a_test3\n");
    printf("Size of `char c` is %d\n", sizeof(p3->c));
    printf("Size of `short s` is %d\n", sizeof(p3->s));
    printf("Size of `int k` is %d\n", sizeof(p3->k));
    printf("Size of `long l` is %d\n", sizeof(p3->l));
    printf("Size of `float f` is %d\n", sizeof(p3->f));
    printf("Size of `double d` is %d\n", sizeof(p3->d));

    // b-Print the size of table3[0] and then the sizeof the whole table3
    printf("\nb-Print the size of table3[0] and then the sizeof the whole table3\n");
    printf("Size of `table3[0]` is %d\n", sizeof(table3[0]));
    printf("Size of `table3` is %d\n", sizeof(table3));

    // c-Print the alignment and address of table3[0]
    printf("\nc-Print the alignment and address of table3[0]\n");
    printf("Alignment of table3[0] is %zu\n", _Alignof(table3[0]));  // not sure if this is correct

    // d-In a loop, print the aligned addresses of the previous and the current elements in table3 (starting with table3[1]), and then the difference between their addresses showing the length of the previous element in the array
    printf("\nd-Show the length of an element in the array\n");
    printf("Address of `table3[0]` is %p\n", &table3[0]);
    printf("Address of `table3[1]` is %p\n", &table3[1]);
    printf("Length of `table3[0]` is %d\n", (size_t)&table3[1] - (size_t)&table3[0]);

    //# a_test4
    print_divider("a_test4");
    p4 = &table4[0];

    // a-Print the sizeof each member type in struct a_test4 (here short and int)
    printf("\na-Print the sizeof each member type in struct a_test4\n");
    printf("Size of `double d` is %d\n", sizeof(p4->d));
    printf("Size of `long l` is %d\n", sizeof(p4->l));
    printf("Size of `float f` is %d\n", sizeof(p4->f));
    printf("Size of `int k` is %d\n", sizeof(p4->k));
    printf("Size of `short s` is %d\n", sizeof(p4->s));
    printf("Size of `char c` is %d\n", sizeof(p4->c));

    // b-Print the size of table4[0] and then the sizeof the whole table4
    printf("\nb-Print the size of table4[0] and then the sizeof the whole table4\n");
    printf("Size of `table4[0]` is %d\n", sizeof(table4[0]));
    printf("Size of `table4` is %d\n", sizeof(table4));

    // c-Print the alignment and address of table4[0]
    printf("\nc-Print the alignment and address of table4[0]\n");
    printf("Alignment of table4[0] is %zu\n", _Alignof(table4[0]));  // not sure if this is correct

    // d-In a loop, print the aligned addresses of the previous and the current elements in table4 (starting with table4[1]), and then the difference between their addresses showing the length of the previous element in the array
    printf("\nd-Show the length of an element in the array\n");
    printf("Address of `table4[0]` is %p\n", &table4[0]);
    printf("Address of `table4[1]` is %p\n", &table4[1]);
    printf("Length of `table4[0]` is %d\n", (size_t)&table4[1] - (size_t)&table4[0]);

}