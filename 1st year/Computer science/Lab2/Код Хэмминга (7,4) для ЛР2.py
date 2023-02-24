number = input("Номер:")
if len(number) != 7:
    print("Номер неправильный")
else:
    r1 = int(number[0])
    r2 = int(number[1])
    i1 = int(number[2])
    r3 = int(number[3])
    i2 = int(number[4])
    i3 = int(number[5])
    i4 = int(number[6])

    s1,s2,s3 = 0,0,0
    s1 = r1 ^ i1 ^ i2 ^ i4 
    s2 = r2 ^ i1 ^ i3 ^ i4
    s3 = r3 ^ i2 ^ i3 ^ i4

    print(f"\nS1 = {r1} ⊕  {i1} ⊕  {i2} ⊕  {i4} = {s1}\n" +
            f"S2 = {r2} ⊕  {i1} ⊕  {i3} ⊕  {i4}  = {s2}\n" +
            f"S3 = {r3} ⊕  {i2} ⊕  {i3} ⊕  {i4}  = {s3}\n")

    errorBit = int(str(s3)+str(s2)+str(s1),2)

    if errorBit == 0:
        print("Вся информация была передана без ошибок!\n")
    else:
        print("Ошибка в битe", errorBit , ". Правильное сообщение: ", end="")
        for i in range(len(number)):
            if i == errorBit-1:
                if number[i] == "0":
                    print(1, end="")
                else:
                    print(0, end="")
            else:
                print(number[i], end="")