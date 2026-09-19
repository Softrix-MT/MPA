# MPA(Multiple Precision Arithmetic/多倍長演算) C++ Object
## 概略
- 多倍長(整数)を演算するC++インラインクラス(MPAInteger.h)
- 多倍長整数演算オブジェクト(MPAInteger)
- (C++/MASM)四則演算ライブラリ(MPAtrial)
## 環境(実装)
- 全てのコードはShift JIS(Windows-31J/CP932)で記述
- C++
- MASM / x86 Assembly(32bit, 64bit)
- Visual Studio(C++/MASM) 6.0/2010/2019によりビルド/テスト
- Multi-precision integer arithmetic
- Big integer (bignum) operations
- Arbitrary-precision integer arithmetic
### フォルダー構造
#### MPAtest
- MPAIntegerテスト用コンソールプログラム(C++)
  - Ver6v0：Visual C++ 6.0用 IDE(.dsw)
  - Ver10v0：Visual Studio 2010用 IDE(.sln)
  - Ver14v2：Visual Studio 2019用 IDE(.sln)
#### MPAtrial
- MPAInteger四則演算ライブラリ(C++/MASM)
  - Ver6v0：Visual C++ 6.0用 IDE(.dsw)
  - Ver10v0：Visual Studio 2010用 IDE(.sln)
  - Ver14v2：Visual Studio 2019用 IDE(.sln)
#### Support
##### MPAInteger.h
- MPAIntegerクラス本体
##### MPAtrialライブラリ
- MPAtri06x86.lib：VC6.0 Release用
- MPAtri06x86d.lib：VC6.0 Debug用
- MPAtri10x86.lib：VC2010 32bit Release用
- MPAtri10x86d.lib：VC2010 32bit Debug用
- MPAtri10x64.lib：VC2010 64bit Release用
- MPAtri10x64d.lib：VC2010 64bit Debug用
- MPAtriE2x86.lib：VC2019 32bit Release用
- MPAtriE2x86d.lib：VC2019 32bit Debuge用
- MPAtriE2x64.lib：VC2019 64bit Release用
- MPAtriE2x64d.lib：VC2019 64bit Debug用
##### MPAtrial.h
- MPAtrialライブラリC++呼び出し用
##### MPAHRESULT.h
- MPAInteger内部でthrow発生時(コンストラクタなど)例外処理用クラス
##### WINtrial.h
- 標準のinclude情報とマクロ
## MPAHRESULT class
### プロパティ
#### `hResult`
- MPAInteger内部でthrow発生時のエラーコード
## MPAtrial class
### 主要メソッド
#### コンストラクタ
##### `MPAInteger(void)`
##### `MPAInteger(UINT_PTR val, bool sign=true)`
- val：符号なし整数値
- sign：(true：正整数 false：負整数)
##### `MPAInteger(LPCVOID pbuf, size_t nBytes, bool sign=true)`
- pbuf：hexデータ(リトルエンディアン整数列)
- bytes：pbufのバイトサイズ
- sign：(true：正整数 false：負整数)
##### `MPAInteger(const TriMPAInteger& val)`
- valからのデータコピー
- MPAInteger ans(val) => ans = val
#### 数値設定
##### `HRESULT Value(UINT_PTR val, bool sign=true);`
- val：符号なし整数値
- sign：(true：正整数 false：負整数)
##### `HRESULT Value(LPCVOID pbuf, size_t bytes, bool sign=true)`
- pbuf：hexデータ(リトルエンディアン整数列)
- bytes：pbufのバイトサイズ
- sign：(true：正整数 false：負整数)
##### `HRESULT Value(const MPAInteger& val)`
- valからのデータコピー
- ans.Value(val) => ans = val
##### `HRESULT Value(LPCTSTR str, int base, size_t length=0)`
- str：文字数列(ビッグエンディアン)(0->9->A->Z->a->z)
  - 36進数以下(0->9->A->Z or 0->9->a->z)
  - 62進数以下(0->9->A->Z->a->z)
- base：使用する基数(2進数～62進数)
- length：str文字列長(0の場合NULL文字まで)

#### 多倍長整数を2進数〜62進数の文字列変換
##### `size_t GetStringLength(int base)`
- 多倍長整数を文字列変換した場合の(終端NULLを含まない文字数)文字数
- base：使用する基数(2進数～62進数)
##### `HRESULT GetString(LPTSTR str, size_t length, int base)`
- str：文字数列を受け取るバッファ
  - 36進数以下(0->9->A->Z or 0->9->a->z)
  - 62進数以下(0->9->A->Z->a->z)
- length：strバッファ文字数
- base：使用する基数(2進数～62進数)

#### 加算
##### `HRESULT Add(val)`
- 符合付き加算
- val：INT_PTRまたはMPAIntegerオブジェクト
- ans.Add(val) => ans += val
##### `HRESULT AddU(val)`
- 絶対値加算
- val：UINT_PTRまたはMPAIntegerオブジェクト
- ans.AddU(val) => ans += val(ansは符号変化しない)
##### `HRESULT Inc(void)`
- Add(1)を実行

#### 減算
##### `HRESULT Sub(val)`
- 符合付き減算
- val：INT_PTRまたはMPAIntegerオブジェクト
- ans.Sub(val) => ans -= val
##### `HRESULT SubU(val)`
- 絶対値減算
- val：UINT_PTRまたはMPAIntegerオブジェクト
- ans.SubU(val) => ans -= val(ansは符号変化しない)
##### `HRESULT Dec(void)`
- Sub(1)を実行

#### 乗算
##### `HRESULT Mul(const MPAInteger& num, const MPAInteger& val)`
- 符合付き乗算
- ans.Mul(val1, val2) => ans = val1 * val2
##### `HRESULT Mul(INT_PTR val)`
- 符合付き乗算
- ans.Mul(val) => ans *= val
##### 'HRESULT MulU(UINT_PTR val)'
- 絶対値乗算
- ans.Mul(val) => ans *= val(ansは符号変化しない)

#### 除算
##### `HRESULT DivS(MPAInteger& num, INT_PTR den)`
- 符合付き除算
- ans.Div(num,den) => ans = num / den
##### 'HRESULT Div(MPAInteger& num, MPAInteger& den, bool denormalize)`
- 符合付き除算
- ans.Div(num,den) => ans = num / den & num = num % den
- denormalize：処理後のden値を非正規化(元の数値に戻す)の実行(true:非正規化 false:正規化)
  - 正規化：最上位ビット(MSB)が1にビットシフト
##### `HRESULT Div(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem)`
- 符合付き除算
- ans.Div(num,den,rem) => ans = num / den & rem = num % den
##### `HRESULT DivU(MPAInteger& num, UINT_PTR den)`
- 絶対値減算
- ans.Div(num,den) => ans = num / den
##### `HRESULT DivU(MPAInteger& num, MPAInteger& den, bool denormalize)`
- 絶対値除算
- ans.Div(num,den) => ans = num / den & num = num % den
- denormalize：処理後のden値を非正規化(元の数値に戻す)の実行(true:非正規化 false:正規化)
  - 正規化：最上位ビット(MSB)が1にビットシフト
##### `HRESULT DivU(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem)`
- 絶対値減算
- ans.Div(num,den,rem) => ans = num / den & rem = num % den

#### 累乗
##### `HRESULT pow(val, exp)`
- ans.pow(val, exp) => ans = val ^ exp

#### 逆数
##### `HRESULT Reciprocal(MPAInteger& val, size_t digits=0, bool denormalize=false)`
- 近似逆数
- ans.Reciprocal(val) => ans = (1 << limb) / val
- digits：逆数のlimb数(桁数)(0：valと同じlimb数)
- denormalize：処理後のval値を非正規化(元の数値に戻す)の実行(true:非正規化 false:正規化)
  - 正規化：最上位ビット(MSB)が1にビットシフト

### 補助メソッド
#### `bool IsEven(void)`
- 偶数/奇数判定(true:偶数 / false:奇数)
#### `void Empty(void)`
- バッファ消去(0桁)
#### `HRESULT Secure(size_t nSize, UINT_PTR val=0)`
- nSize：領域確保を保証するUINT_PTR数
- val：拡張された領域を埋める値
#### `size_t Adjust(void)`
- 上位(MSB)のゼロ領域を領域から除外
#### `size_t Length(void)`
- 有効な値が格納されているUINT_PTR数
#### `HRESULT Random(size_t nBytes, bool sign=true)`
- nBytes：指定されたバイトサイズの疑似乱数値を格納
- sign：正数/負数フラグ設定
#### `HRESULT　Insert(size_t limb, UINT_PTR val=0)`
- limb：UINT_PTRをlimb数分左シフト
- val：シフト後下位領域を埋める値
#### `HRESULT Higher(MPAInteger& high, size_t limb, bool allocation)`
- thisオブジェクトからlimbサイズhighに領域をコピーまたはアドレスコピー
- high：領域を受け取るオブジェクト
- limb：this領域からlimbサイズhighにコピー
- allocation：true=領域確保とデータコピー　false=メモリーアドレスコピー
#### `Swap(MPAInteger& val1, MPAInteger& val2)`
- val1とval2のデータ(数値メモリーアドレスと符号)を入れ替える
#### `HRESULT SplitU(MPAInteger& high, MPAInteger& low, size_t limb, bool allocation)`
- 絶対値分割(正/負)フラグはコピーされない(high,lowは常に正の値)
- thisオブジェクトからlimbサイズ位置の上位をhigh下位をlowにコピーまたはアドレスコピー
- limb：this領域から分割する位置
- allocation：true=領域確保＆領域コピー　false=メモリーアドレスコピー
#### `HRESULT Merge(size_t exp, const MPAInteger& val)`
- thisオブジェクトをexp左シフトしval値を下位にコピー
- valのサイズがexpより大きい場合は上位expサイズ分コピー
#### `int Cmp(val)`
- 符合付き比較
- val1.Cmp(val2) => -1:(val1 < val2) 0:(val1 == val2) 1:(val1 > val2)
#### `int CmpU(val)`
- 絶対値比較
- val1.Cmp(val2) => -1:(val1 < val2) 0:(val1 == val2) 1:(val1 > val2)
#### `void NotValue(void)`
- 数値部１の補数変換
#### `void NegValue(void)`
- 数値部２の補数変換
#### `void NegSign(void)`
- 符号反転
#### `HRESULT Shift(INT_PTR nBits)`
- nBits：(+値：左シフト -値:右シフト)
#### `HRESULT Shl(UINT_PTR nBits)`
- 左シフト(1ビット当たり2倍)
#### `void Shr(UINT_PTR nBits)`
- 右シフト(1ビット当たり1/2倍)
