from random import randint

def generate_random_test(name = 'test'):
    v_number = randint(0,100)
    edges = set()
    for v in range(v_number):
        edges.add((v, (v+1)%v_number))

    a = randint(0, v_number-1)
    b = randint(0, v_number-1)
    while a==b:
        b = randint(0, v_number-1)

    if a<b:
        edges.add((a,b))
        print(f'Dodano most: {a}-{b}')
    else:
        edges.add((b,a))
        print(f'Dodano most: {b}-{a}')

    with open(f'{name}.txt','w') as file:
        file.write(f'{v_number}\n')

        for a,b in edges:
            file.write(f'{a} {b}\n')

        file.close()

if __name__ == '__main__':
    generate_random_test()
