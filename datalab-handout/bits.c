/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  //using !(x+y)==!x&!y
  return ~(~(x & ~y) & ~(~x & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{

  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  //notice that !(Umax+1)==1,!(Tmax+1)==0,which identifies them
  //!((x+1)^(~0)^x) decides whether x is Tmax or Umax(-1),!!(x+1) choose Tmax
  //result
  return !((x + 1) ^ (~0) ^ x) & !!(x + 1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  int x0 = (0xAA);
  int x1 = (0xAA << 8);
  int x2 = (0xAA << 16);
  int x3 = (0xAA << 24);
  int x4 = x0 + x1 + x2 + x3;
  return !((x & x4) ^ x4);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  //only focus on the 32bit to see if it's negetive
  int lower = x + (~0x30 + 1);
  int upper = 0x39 + (~x + 1);
  int z = 1 << 31;
  return !((lower | upper) & z);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  //!!x made x be logical
  int w = !!x;
  //if w==0,nw==0,ifw==1,nw==0xffffffff(-1)
  int nw = ~w + 1;
  return (nw & y) | (~nw & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{ 
  //get sign of x and y
  int sx=(x>>31)&1;
  int sy=(y>>31)&1;
  //xnyp means neg. overflow,vice versa.
  int xnyp=!(sx^1)&!(sy^0);
  int xpyn=!(sx^0)&!(sy^1);
  int diff=x+(~y+1);
  int sdf=(diff>>31)&1;
  int is_euql=!diff;
 return xnyp|is_euql|(sdf&!xpyn);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x)
{
  x=x|x>>16;
  x=x|x>>8;
  x=x|x>>4;
  x=x|x>>2;
  x=x|x>>1;
  return (x&1)^1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{ int nx,x55,x33,x0f,x00ff,x0000ffff;
  int mask=(x&(1<<31))>>31;
  //if x<0,find leftmost 0 throgh ~x and creat a mask
  int x0=((~x)&mask)|(x&(~mask));
  x0=x0|x0>>16;
  x0=x0|x0>>8;
  x0=x0|x0>>4;
  x0=x0|x0>>2;
  x0=x0|x0>>1;
  //creat mask for neg.x 
  nx=((x0<<1)+1)&x;
  x=(nx&mask)|(x&(~mask));
  //creat a mask that indicate the leftmost 1,0x60->0x7F
  //if we use xor rather than or,if will work as a parity teller
  x=x|x>>16;
  x=x|x>>8;
  x=x|x>>4;
  x=x|x>>2;
  x=x|x>>1;
  //creat 0x55555555,0x33333333,0x0f0f0f0f,0x00ff00ff,0x0000ffff
  x55=0x55+(0x55<<8)+(0x55<<16)+(0x55<<24);
  x33=0x33+(0x33<<8)+(0x33<<16)+(0x33<<24);
  x0f=0x0f+(0x0f<<8)+(0x0f<<16)+(0x0f<<24);
  x00ff=0xff+(0xff<<16);
  x0000ffff=0xff+(0xff<<8);
  //count numbers of 1 using divide&conquer
  x = (x & x55) + ((x >> 1) & x55);
  x = (x & x33) + ((x >> 2) & x33);
  x = (x & x0f) + ((x >> 4) & x0f);
  x = (x & x00ff) + ((x >> 8) & x00ff);
  x = (x & x0000ffff) + ((x >> 16)& x0000ffff);
  return ((x+1)&~mask)|(x&mask);
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{ 
  unsigned sign=uf>>31;
  unsigned raw_exp=(uf&0x7f800000)>>23;
  unsigned f=uf&0x007fffff;
  unsigned mask=0x00800000;
  if(raw_exp>0&&raw_exp<255){
    //exp==e-bias
    raw_exp=raw_exp+1;
    if(raw_exp>=255){
      raw_exp=255;
      f=0;
    }
  }
  else if(raw_exp==0){
    //1-bias==1-(2^(k-1)-1)==-126
    //for example (3/8)*2->0.011 to 0.11,(7/8)*2-> 0.111 to 1.110
    //in the second case ,1 dropped because in defalt it is 1.xxx,we need to
    //left shift 1,thus 1.110 would be 1.1100,and mask it to get 0.1100
    if(((f<<1)&mask)>>23!=1)
      f=f<<1;
    else{
      raw_exp=raw_exp+1;
      f=(f<<1)&0x007fffff;
    }
  }
  //deal with NaN
  else if(raw_exp==255&&f!=0)
    return uf;
  return (sign<<31)+(raw_exp<<23)+f;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{ unsigned sign=uf>>31;
  unsigned raw_exp=(uf&0x7f800000)>>23;
  unsigned f=(uf&0x007fffff)|0x00800000;
  unsigned ret=0;
  int exp=0;
  if(raw_exp>0&&raw_exp<255){
    exp=raw_exp-127;
    //if exp==0,f>>23 will be 1
    //we are not going to consider rounding if exp==-1
    if(exp<0)
      return 0;
    else {
    if(exp<23)
      ret=(f>>(23-exp));
    //if exp==31,leftmost will be 1,which means number is too big
    else if(exp<31)
      ret=f<<(exp-23);
      else
        return 0x80000000;
      }
  }
  //raw_exp==0 means number is too small
  else if(raw_exp==0)
    return 0;
  
  //deal with NaN&infinity
  else if(raw_exp==255)
    return 0x80000000;
  return sign==1?(~ret+1):ret;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x)
{ unsigned sign=0;
  unsigned raw_exp;
  unsigned f;
  unsigned ret=0;
  int exp=0;
  if(x>=(-126)&&x<=127){
    raw_exp=127+x;
    f=0;
  }
  else if(x>=(-126-23)&&x<(-126)){
    raw_exp=0;
    exp=-126;
    f=1<<(23-(exp-x));
  }
  else if(x<(-126-23)){
    raw_exp=0;
    f=0;
  }
  else if(x>127)
  {
    raw_exp=255;
    f=0;
  }
  else{
    raw_exp=255;
    f=-1;
  }
  ret=(sign<<31)+(raw_exp<<23)+f;
  return ret;
}
