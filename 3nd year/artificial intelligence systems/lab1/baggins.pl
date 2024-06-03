marrieds('Бальбо Бэггинс', 'Боффин Берилла').
marrieds('Мунго Бэггинс', 'Лаура Грубб').
marrieds('Панси Бэггинс', 'Фастольф Булджер').
marrieds('Понто Бэггинс', 'Мимоза Прыгг').
marrieds('Ларго Бэггинс', 'Танта Волынщица').
marrieds('Лилия Бэггинс', 'Того Дебеллинг').
marrieds('Бунго Бэггинс', 'Белладонна Тукк').
marrieds('Бельба Бэггинс', 'Рудигар Булджер').
marrieds('Лонга Бэггинс', 'Камелия Саквилль').
marrieds('Линда Бэггинс', 'Бодо Большеступ').
marrieds('Бинго Бэггинс', 'Чика Кубб').
marrieds('Роза Бэггинс', 'Хильгдрим Тукк').
marrieds('Фоско Бэггинс', 'Руби Бульджер').
marrieds('Отто Саквилль-Бэггинс', 'Лобелия Перестегинс').
marrieds('Поско Бэггинс', 'Джилли Русое Колечко').
marrieds('Приска Бэггинс', 'Виллибальд Блиджер').
marrieds('Дрого Бэггинс', 'Примула Брэндибек').
marrieds('Маковка Бэггинс', 'Филиберт Бульджер').
marrieds('Пиония Бэггинс', 'Мило Рытвинг').
marrieds('Ромашка Бэггинс', 'Гриффо Боффин').

children('Мунго Бэггинс', 'Бальбо Бэггинс').
children('Панси Бэггинс', 'Бальбо Бэггинс').
children('Понто Бэггинс', 'Бальбо Бэггинс').
children('Ларго Бэггинс', 'Бальбо Бэггинс').
children('Лилия Бэггинс', 'Бальбо Бэггинс').
children('Бунго Бэггинс', 'Мунго Бэггинс').
children('Бельба Бэггинс', 'Мунго Бэггинс').
children('Лонго Бэггинс', 'Мунго Бэггинс').
children('Линда Бэггинс', 'Мунго Бэггинс').
children('Бинго Бэггинс', 'Мунго Бэггинс').
children('Поло Бэггинс', 'Понто Бэггинс').
children('Роза Бэггинс', 'Понто Бэггинс').
children('Фоско Бэггинс', 'Ларго Бэггинс').
children('Бильбо Бэггинс', 'Бунго Бэггинс').
children('Ото Саквилль-Бэггинс', 'Лонго Бэггинс').
children('Одо Большеступ', 'Линда Бэггинс').
children('Фалко Кубб-Бэггинс', 'Бинго Бэггинс').
children('Перегрин Тукк', 'Роза Бэггинс').
children('Мериадок Тукк', 'Роза Бэггинс').
children('Поско Бэггинс', 'Поло Бэггинс').
children('Приска Бэггинс', 'Поло Бэггинс').
children('Дора Бэггинс', 'Фоско Бэггинс').
children('Дрого Бэггинс', 'Фоско Бэггинс').
children('Дудо Бэггинс', 'Фоско Бэггинс').
children('Понто Второй Бэггинс', 'Поско Бэггинс').
children('Порто Бэггинс', 'Поско Бэггинс').
children('Пиония Бэггинс', 'Поско Бэггинс').
children('Фродо Бэггинс', 'Дрого Бэггинс').
children('Ромашка Бэггинс', 'Дудо Бэггинс').
children('Анжелика Бэггинс', 'Понто Второй Бэггинс').
children('Моско Рытвинг', 'Пиония Бэггинс').
children('Моро Рытвинг', 'Пиония Бэггинс').
children('Мирта Рытвинг', 'Пиония Бэггинс').
children('Минто Рытвинг', 'Пиония Бэггинс').
children('Лото Саквилль-Бэггинс', 'Ото Саквилль-Бэггинс').
children('Оло Большеступ', 'Одо Большеступ').
children('Маковка Кубб-Бэггинс', 'Фалко Кубб-Бэггинс').
children('Санхо Большеступ', 'Оло Большеступ').

children(C, P) :- 
   marrieds(P1, P), children(C, P1), !.

grandparent(C, GP) :- 
    children(C, P), children(P, GP).

siblings(C1, C2) :-
    children(C1, P), children(C2, P), C1 \= C2.

uncles(C, U) :-
    children(C, P), siblings(P, U).

cousins(C, Co) :-
    uncles(C, U), children(Co, U).

is_married(P1, P2) :-
    marrieds(P1, P2).
is_married(P1, P2) :-
    marrieds(P2, P1).

ancestor(C, A) :-
    children(C, A).
ancestor(C, A) :-
    children(C, C1),
    ancestor(C1, A).

generation_diff_help(C, A, N, N1) :-
    children(C, A), N is N1.
generation_diff_help(C, A, N, N1) :-
    N2 is N1 + 1,
    children(C, C1),
    generation_diff_help(C1, A, N, N2).
generation_diff(C, A, N) :- 
    generation_diff_help(C, A, N, 1).

in_one_generation(C, C1) :- 
    generation_diff(C, 'Бальбо Бэггинс', N),
    generation_diff(C1, 'Бальбо Бэггинс', N),
    C1 \= C.

grandgreatparents(C, GGP) :-
    generation_diff(C, GGP, 3).
    
