# MPA(Multiple Precision Arithmetic/Multiprecision Arithmetic) C++ Object
## Overview
- C++ inline class for multiprecision (integer) arithmetic (MPAInteger.h)
- Multiprecision integer arithmetic object (MPAInteger)
- (C++/MASM) arithmetic library for the four basic operations (MPAtrial)
## Environment (Implementation)
- All code is written in Shift JIS (Windows-31J/CP932)
- C++
- MASM / x86 Assembly (32-bit, 64-bit)
- Built and tested with Visual Studio (C++/MASM) 6.0/2010/2019
- Multi-precision integer arithmetic
- Big integer (bignum) operations
- Arbitrary-precision integer arithmetic
### Folder Structure
#### MPAtest
- Console program for testing MPAInteger (C++)
  - Ver6v0: IDE for Visual C++ 6.0 (.dsw)
  - Ver10v0: IDE for Visual Studio 2010 (.sln)
  - Ver14v2: IDE for Visual Studio 2019 (.sln)
#### MPAtrial
- MPAInteger arithmetic library for the four basic operations (C++/MASM)
  - Ver6v0: IDE for Visual C++ 6.0 (.dsw)
  - Ver10v0: IDE for Visual Studio 2010 (.sln)
  - Ver14v2: IDE for Visual Studio 2019 (.sln)
#### Support
##### MPAInteger.h
- MPAInteger class implementation
##### MPAtrial Library
- MPAtri06x86.lib: For VC6.0 Release
- MPAtri06x86d.lib: For VC6.0 Debug
- MPAtri10x86.lib: For VC2010 32-bit Release
- MPAtri10x86d.lib: For VC2010 32-bit Debug
- MPAtri10x64.lib: For VC2010 64-bit Release
- MPAtri10x64d.lib: For VC2010 64-bit Debug
- MPAtriE2x86.lib: For VC2019 32-bit Release
- MPAtriE2x86d.lib: For VC2019 32-bit Debuge
- MPAtriE2x64.lib: For VC2019 64-bit Release
- MPAtriE2x64d.lib: For VC2019 64-bit Debug
##### MPAtrial.h
- For calling the MPAtrial library from C++
##### MPAHRESULT.h
- Class for exception handling when an exception is thrown inside MPAInteger (e.g., by a constructor)
##### WINtrial.h
- Standard include information and macros
## MPAHRESULT Class
### Properties
#### `hResult`
- Error code when an exception is thrown inside MPAInteger
## MPAInteger Class
### Main Methods
#### Constructors
##### `MPAInteger(void)`
##### `MPAInteger(UINT_PTR val, bool sign=true)`
- val: Unsigned integer value
- sign: (true: positive integer, false: negative integer)
##### `MPAInteger(LPCVOID pbuf, size_t nBytes, bool sign=true)`
- pbuf: Hex data (little-endian integer sequence)
- bytes: Byte size of pbuf
- sign: (true: positive integer, false: negative integer)
##### `MPAInteger(const TriMPAInteger& val)`
- Copy data from val
- MPAInteger ans(val) => ans = val
#### Setting a Value
##### `HRESULT Value(UINT_PTR val, bool sign=true);`
- val: Unsigned integer value
- sign: (true: positive integer, false: negative integer)
##### `HRESULT Value(LPCVOID pbuf, size_t bytes, bool sign=true)`
- pbuf: Hex data (little-endian integer sequence)
- bytes: Byte size of pbuf
- sign: (true: positive integer, false: negative integer)
##### `HRESULT Value(const MPAInteger& val)`
- Copy data from val
- ans.Value(val) => ans = val
##### `HRESULT Value(LPCTSTR str, int base, size_t length=0)`
- str: Character string (big-endian) (0->9->A->Z->a->z)
  - Up to base 36 (0->9->A->Z or 0->9->a->z)
  - Up to base 62 (0->9->A->Z->a->z)
- base: Radix to use (base 2 to base 62)
- length: Length of the str string (0: up to the null terminator)

#### Convert Multiprecision Integers to Strings in Base 2–62
##### `size_t GetStringLength(int base)`
- Number of characters when converting a multiprecision integer to a string (excluding the terminating NULL)
- base: Radix to use (base 2 to base 62)
##### `HRESULT GetString(LPTSTR str, size_t length, int base)`
- str: Buffer to receive the character string
  - Up to base 36 (0->9->A->Z or 0->9->a->z)
  - Up to base 62 (0->9->A->Z->a->z)
- length: Number of characters in the str buffer
- base: Radix to use (base 2 to base 62)

#### Addition
##### `HRESULT Add(val)`
- Signed addition
- val: INT_PTR or MPAInteger object
- ans.Add(val) => ans += val
##### `HRESULT AddU(val)`
- Absolute-value addition
- val: UINT_PTR or MPAInteger object
- ans.AddU(val) => ans += val (the sign of ans does not change)
##### `HRESULT Inc(void)`
- Executes Add(1)

#### Subtraction
##### `HRESULT Sub(val)`
- Signed subtraction
- val: INT_PTR or MPAInteger object
- ans.Sub(val) => ans -= val
##### `HRESULT SubU(val)`
- Absolute-value subtraction
- val: UINT_PTR or MPAInteger object
- ans.SubU(val) => ans -= val (the sign of ans does not change)
##### `HRESULT Dec(void)`
- Executes Sub(1)

#### Multiplication
##### `HRESULT Mul(const MPAInteger& num, const MPAInteger& val)`
- Signed multiplication
- ans.Mul(val1, val2) => ans = val1 * val2
##### `HRESULT Mul(INT_PTR val)`
- Signed multiplication
- ans.Mul(val) => ans *= val
##### `HRESULT MulU(UINT_PTR val)`
- Absolute-value multiplication
- ans.Mul(val) => ans *= val (the sign of ans does not change)

#### Division
##### `HRESULT Div(MPAInteger& num, INT_PTR den)`
- Signed division
- ans.Div(num,den) => ans = num / den
##### `HRESULT Div(MPAInteger& num, MPAInteger& den, bool denormalize)`
- Signed division
- ans.Div(num,den) => ans = num / den & num = num % den
- denormalize: Execute denormalization (restore the original value) of den after processing (true: denormalize, false: normalize)
  - Normalization: Bit-shift so that the most significant bit (MSB) is 1
##### `HRESULT Div(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem)`
- Signed division
- ans.Div(num,den,rem) => ans = num / den & rem = num % den
##### `HRESULT DivU(MPAInteger& num, UINT_PTR den)`
- Absolute-value subtraction
- ans.Div(num,den) => ans = num / den & num = num % den
##### `HRESULT DivU(MPAInteger& num, MPAInteger& den, bool denormalize)`
- Absolute-value division
- ans.Div(num,den) => ans = num / den & num = num % den
- denormalize: Execute denormalization (restore the original value) of den after processing (true: denormalize, false: normalize)
  - Normalization: Bit-shift so that the most significant bit (MSB) is 1
##### `HRESULT DivU(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem)`
- Absolute-value subtraction
- ans.Div(num,den,rem) => ans = num / den & rem = num % den

#### Exponentiation
##### `HRESULT pow(val, exp)`
- ans.pow(val, exp) => ans = val ^ exp

#### Reciprocal
##### `HRESULT Reciprocal(MPAInteger& val, size_t digits=0, bool denormalize=false)`
- Approximate reciprocal
- ans.Reciprocal(val) => ans = (1 << limb) / val
- digits: Number of limbs (digits) of the reciprocal (0: same number of limbs as val)
- denormalize: Execute denormalization (restore the original value) of val after processing (true: denormalize, false: normalize)
  - Normalization: Bit-shift so that the most significant bit (MSB) is 1

### Auxiliary Methods
#### `bool IsEven(void)`
- Determines whether the value is even or odd (true: even / false: odd)
#### `void Empty(void)`
- Clears the buffer (0 digits)
#### `HRESULT Secure(size_t nSize, UINT_PTR val=0)`
- nSize: Number of UINT_PTR elements for which storage is guaranteed
- val: Value used to fill the extended area
#### `size_t Adjust(void)`
- Excludes the zero-filled upper (MSB) area from the allocated area
#### `size_t Length(void)`
- Number of UINT_PTR elements containing valid values
#### `HRESULT Random(size_t nBytes, bool sign=true)`
- nBytes: Stores a pseudo-random value of the specified byte size
- sign: Sets the positive/negative sign flag
#### `HRESULT　Insert(size_t limb, UINT_PTR val=0)`
- limb: Left-shifts UINT_PTR by the specified number of limbs
- val: Value used to fill the lower area after the shift
#### `HRESULT Higher(MPAInteger& high, size_t limb, bool allocation)`
- Copies the specified limb-sized upper area from this object to high, either by copying the data or the memory address
- high: Object that receives the area
- limb: Number of limbs to copy from this object to high
- allocation: true = allocate storage and copy data, false = copy the memory address
#### `void Swap(MPAInteger& val1, MPAInteger& val2)`
- Swaps the data (numeric memory address and sign) of val1 and val2
#### `HRESULT SplitU(MPAInteger& high, MPAInteger& low, size_t limb, bool allocation)`
- Splits the absolute value (the positive/negative sign flag is not copied; high and low are always positive)
- Copies or address-copies the upper and lower portions of this object at the specified limb position to high and low
- limb: Position at which to split this object's area
- allocation: true = allocate storage and copy the data, false = copy the memory address
#### `HRESULT Merge(size_t exp, const MPAInteger& val)`
- Left-shifts this object by exp and copies the value of val into the lower area
- If the size of val is greater than exp, copies the upper exp-sized portion
#### `int Cmp(val)`
- Signed comparison
- val1.Cmp(val2) => -1:(val1 < val2) 0:(val1 == val2) 1:(val1 > val2)
#### `int CmpU(val)`
- Absolute-value comparison
- val1.Cmp(val2) => -1:(val1 < val2) 0:(val1 == val2) 1:(val1 > val2)
#### `void NotValue(void)`
- Converts the numeric portion to one's complement
#### `void NegValue(void)`
- Converts the numeric portion to two's complement
#### `void NegSign(void)`
- Reverses the sign
#### `HRESULT Shift(INT_PTR nBits)`
- nBits: (+ value: left shift, - value: right shift)
#### `HRESULT Shl(UINT_PTR nBits)`
- Left shift (doubles for every 1-bit shift)
#### `void Shr(UINT_PTR nBits)`
- Right shift (halves for every 1-bit shift)
