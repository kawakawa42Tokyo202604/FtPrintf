# FtPrintf

## English

A C implementation of formatted output: inserting numbers and strings into text. For example, `ft_printf("score: %d\n", 42)` replaces `%d` with an integer and prints `score: 42`.

Building creates `libftprintf.a`, a library that exposes `ft_printf` to C programs. The function also returns the number of characters printed.

### Supported conversions

| Specifier | Output |
| --- | --- |
| `%c` | Character |
| `%s` | String |
| `%p` | Pointer address in hexadecimal |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` / `%X` | Hexadecimal integer, lowercase / uppercase |
| `%%` | A literal `%` |

### Build and try

Requires a C compiler and Make. The supplied [main.c](main.c) demonstrates the library.

```sh
make
make run
```

`make` builds `libftprintf.a`; `make example` builds the demonstration executable. `make run` prints `answer: 42`.

### Implementation

Uses variable arguments from `stdarg.h` and dispatches output by conversion specifier. It returns the output character count, or `-1` on error.

### Tests

```sh
make test
```

Checks every supported conversion, empty strings, NUL characters, integer limits, byte counts, and write errors.

## 日本語

文字列の中に数値や別の文字列を埋め込んで表示する、Cの `printf` 関数を自作したものです。例えば `ft_printf("score: %d\n", 42)` は、`%d` を整数に置き換えて `score: 42` と表示します。

ビルドすると、Cプログラムから `ft_printf` を呼び出せるライブラリファイル `libftprintf.a` ができます。出力内容に加え、表示した文字数も戻り値で受け取れます。

### 対応する変換指定子

| 指定子 | 出力 |
| --- | --- |
| `%c` | 文字 |
| `%s` | 文字列 |
| `%p` | ポインタ値（16進数） |
| `%d` / `%i` | 符号付き10進整数 |
| `%u` | 符号なし10進整数 |
| `%x` / `%X` | 16進整数（小文字 / 大文字） |
| `%%` | `%` |

### ビルドと使用例

Cコンパイラ・Make が必要です。付属の [main.c](main.c) でライブラリの使用例を実行できます。

```sh
make
make run
```

`make` は `libftprintf.a`、`make example` はそれを呼び出す実行例をビルドします。`make run` では `answer: 42` を表示します。

### 実装メモ

`stdarg.h` の可変長引数を使い、変換指定子ごとに出力処理を分けています。戻り値は出力した文字数で、エラー時は `-1` です。

### テスト

```sh
make test
```

対応する全変換指定子、空文字列、NUL文字、整数境界値、出力バイト数、書き込みエラーを確認します。
