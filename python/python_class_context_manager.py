class Sample:
    def __init__(self, name):
        self.name = name

    def __enter__(self):
        print('Enter!')
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        print('Exit!')

if __name__ == '__main__':
    with Sample('Test!') as sample:
        print(sample.name)
