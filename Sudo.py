import random
import time


def checkRow(x, y):
    rep = [0] * 10
    rStart = (x // 9) * 9
    for rStart in range(rStart, rStart + 9):
        rep[board[rStart * 9 + y]] += 1

    for c in rep[1:]:
        if c > 1:
            return False
    return True


def checkCol(x, y):
    rep = [0] * 10
    rStart = (y // 9) * 9
    for rStart in range(rStart, rStart + 9):
        rep[board[rStart + 9 * x]] += 1

    for c in rep[1:]:
        if c > 1:
            return False
    return True


def checkBox(x, y):
    rep = [0] * 10
    rStart = (x // 3) * 27 + (y // 3) * 3
    # for rStart in range(rStart + 9):
    #    rep[board[rStart + 9 * x]] += 1
    # print(rStart)
    for rStart in range(rStart, rStart + 3):
        rep[board[rStart]] += 1
    rStart += 7
    # print(rStart)
    for rStart in range(rStart, rStart + 3):
        rep[board[rStart]] += 1
    rStart += 7
    # print(rStart)
    for rStart in range(rStart, rStart + 3):
        rep[board[rStart]] += 1

    # print(rStart)

    for c in rep[1:]:
        if c > 1:
            return False
    return True


def show():
    for i in range(0, 81, 9):
        print(board[i : i + 3], board[i + 3 : i + 6], board[i + 6 : i + 9])
    pass


def fill(board, idx=0):
    # Caso base (salida)
    if idx == 81:
        return True

    posi = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    while posi:
        ran = random.choice(posi)
        x, y = idx // 9, idx % 9

        board[idx] = ran

        print(checkRow(x, y) and checkCol(x, y) and checkBox(x, y))
        show()
        time.sleep(0.5)
        if checkRow(x, y) and checkCol(x, y) and checkBox(x, y):

            if fill(board, idx + 1):
                return True

        board[idx] = 0
        posi.remove(ran)
        print(posi, x, y, ran)
    return False


board = [1, 1] + [0] * 79
show()
fill(board)
# posi = [1, 2, 3, 4, 5, 6, 7, 8, 9]
# ran = random.choice(posi)
# print(ran)
# posi.remove(ran)
# print(len(posi))