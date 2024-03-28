# Лабораторная работа 2

**Название:** "Разработка драйверов блочных устройств"

**Цель работы:** получить знания и навыки разработки драйверов блочных 
устройств для операционной системы Linux.

**Вариант:** 6

## Описание функциональности драйвера

Один первчиный раздел размером 12 МБайт и один расширенный раздел, содержащий два логических раздела размером 15 МБайт и 23 МБайт. 

Каждый записываемый байт должен возводиться в квадрат.
## Инструкция по сборке

Сборка модуля:

```
make
```

Сборка с последующей установкой:

```
make install
```

Отключение модуля:

```
make uninstall
```

Очистка артефактов сборки:

```
make clean
```

## Инструкция пользователя

Для начала проверим, что диск дейтвительно существет, выполнив команду:

```
fdisk -l /dev/mydisk
```

Получаем результат:
