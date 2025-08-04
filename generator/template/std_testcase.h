#ifndef STD__TEST_CASE__H
#define STD__TEST_CASE__H

#include <cstdlib>
#include <memory>

#define ALLOCA alloca

/* classes used in some test cases as a custom type */
class TwoIntsClass {
 public:  // Needed to access variables from label files
  int intOne;
  int intTwo;
};

class OneIntClass {
 public:  // Needed to access variables from label files
  int intOne;
};

/* struct used in some test cases as a custom type */
typedef struct _twoIntsStruct {
  int intOne;
  int intTwo;
} twoIntsStruct;

/* The variables below are declared "const", so a tool should
   be able to identify that reads of these will always return their
   initialized values. */
extern const int GLOBAL_CONST_TRUE;  /* true */
extern const int GLOBAL_CONST_FALSE; /* false */
extern const int GLOBAL_CONST_FIVE;  /* 5 */

/* The variables below are not defined as "const", but are never
   assigned any other value, so a tool should be able to identify that
   reads of these will always return their initialized values. */
extern int globalTrue;  /* true */
extern int globalFalse; /* false */
extern int globalFive;  /* 5 */

/* IO functions */

void printLine(const char* line);
void printWLine(const wchar_t* line);
void printIntLine(int intNumber);
void printShortLine(short shortNumber);
void printFloatLine(float floatNumber);
void printLongLine(long longNumber);
void printLongLongLine(int64_t longLongIntNumber);
void printSizeTLine(size_t sizeTNumber);
void printHexCharLine(char charHex);
void printWcharLine(wchar_t wideChar);
void printUnsignedLine(unsigned unsignedNumber);
void printHexUnsignedCharLine(unsigned char unsignedCharacter);
void printDoubleLine(double doubleNumber);
void printStructLine(const twoIntsStruct* structTwoIntsStruct);
void printBytesLine(const unsigned char* bytes, size_t numBytes);

/* Return value functions */
int globalReturnsTrue();
int globalReturnsFalse();
int globalReturnsTrueOrFalse(); /* do not define */

/* Stub function */
void doNothingUndefined(); /* do not define */
void doNothingDefined();

#endif  // STD__TEST_CASE__H
