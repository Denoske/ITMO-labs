import re
isu = 282581 #int(input())
text1="Люблю этот смайл ^_^ но, мне достался ;</"
text2=" ;</ ;</ ;</ ;</ ;</ ;</ набор символов каких то"
text3= ";) :) ;>/ X-{P"
text4= "Спорим тут нет смайликов?"
text5= "8-(  ;</ :-0 =<)"
texts= [text1,text2,text3,text4,text5]
#print("Ваши варианты = ", isu%5, isu%4, isu%7)
eyes = [":", ";", "X", "8", "="]
noses = ["-", "<", "-{", "<{"]
mouths = ["(", ")", "O", "|", "\ ", "/", "P"]
smile = eyes[isu%5] + noses[isu%4] + mouths[isu%7]
print("Ваш смайл=  ",smile)
#message= 'Это мой смайлик - ;</ . А это второй :-).'
print("Вы хотите проверить сами? (yes,no)")
answer= input()
if answer=="yes":
    print("Хорошо, тогда введите ваш текст")
    message= input()
     
elif answer=="no":
    print("Тогда выбирайте какой из всех текстов проверить:")
    for i in range(len(texts)):
        print("[",i,"]",texts[i])
    print("Введите цифру текста который надо проверить")
    what= int(input())
    message = texts[what]


findsmile = len(re.findall(smile, message))

print("Количество вашего смайла", smile, 'равно -', findsmile,'\nиз текста- ', message )