N = 81

def digram(n: int) -> str:
    return chr(ord('A') + n // 26) + chr(ord('A') + n % 26)

def digram_range(*args) -> str:
    return ','.join(digram(k) for k in range(*args))

def letter_range(n) -> list:
    return [chr(ord('A') + k) for k in range(n)]

for i in range(5):
    lines = [f"#define FOR_{i}({', '.join(letter_range(i) + ['M'])})"]
    lines += [f'M(__VA_ARGS__ __VA_OPT__(,) {c})' for c in letter_range(i)]
    print(' \\\n\t'.join(lines))
for i in range(5, N):
    lines = [f'#define FOR_{i}({digram_range(i)}, M, ...)']
    if i % 3:
        if i % 2:
            lines += [
                f'M(__VA_ARGS__ __VA_OPT__(,) {digram(0)})',
                f'FOR_{i - 1}({digram_range(1, i)}, M __VA_OPT__(,) __VA_ARGS__)',
            ]
        else:
            lines += [
                f'FOR_{i // 2}({digram_range(0, i // 2)}, M __VA_OPT__(,) __VA_ARGS__)',
                f'FOR_{i // 2}({digram_range(i // 2, i)}, M __VA_OPT__(,) __VA_ARGS__)',
            ]
    else:
        lines += [
            f'FOR_{i // 3}({digram_range(0, i // 3)}, M __VA_OPT__(,) __VA_ARGS__)',
            f'FOR_{i // 3}({digram_range(i // 3, 2 * i // 3)}, M __VA_OPT__(,) __VA_ARGS__)',
            f'FOR_{i // 3}({digram_range(2 * i // 3, i)}, M __VA_OPT__(,) __VA_ARGS__)',
        ]
    print(' \\\n\t'.join(lines))
