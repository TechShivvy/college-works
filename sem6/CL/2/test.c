{
    int a = 5, b = 10;
    float x = 3.14, y = 6.28;

    // Arithmetic operators
    int c = a + b;
    int d = b - a;
    float e = x * y;
    float f = y / x;

    // Arithmetic assignment operators
    a += 2;
    b -= 3;
    x *= 2;
    y /= 2;

    // Logical operators
    if (a < b && x > y) {
        printf("a is less than b and x is greater than y.\n");
    } else {
        printf("a is not less than b or x is not greater than y.\n");
    }

    // Relational operators
    if (a == b) {
        printf("a is equal to b.\n");
    } else if (a != b) {
        printf("a is not equal to b.\n");
    } else if (a > b) {
        printf("a is greater than b.\n");
    } else if (a < b) {
        printf("a is less than b.\n");
    } else if (a >= b) {
        printf("a is greater than or equal to b.\n");
    } else if (a <= b) {
        printf("a is less than or equal to b.\n");
    }

    // Bitwise operators
    int g = a & b;
    int h = a | b;
    int i = a ^ b;
    g = a<<10;
    h = c>>2;

    // Unary operators
    int j = a++;
    int l = -a;

    // Assignment operator
    int m = 0;
    m = a;

    // Special character
    char ch = '\n';

    // Function calls
    printf("The sum of a and b is %d\n", c);
    printf("The difference between b and a is %d\n", d);
    printf("The product of x and y is %f\n", e);
    printf("The quotient of y and x is %f\n", f);
    printf("The bitwise AND of a and b is %d\n", g);
    printf("The bitwise OR of a and b is %d\n", h);
    printf("The bitwise XOR of a and b is %d\n", i);
    printf("The logical NOT of a is %d\n", j);
    printf("The one's complement of a is %d\n", k);
    printf("The negation of a is %d\n", l);

    return 0;
}
