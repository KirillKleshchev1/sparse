def main():
    with open('A', 'wb') as f:
        w = [0 for _ in range(4194304)] + [1]
        w[0] = 1
        w[10000] = 1
        f.write(bytearray(w))


if __name__ == "__main__":
    main()
