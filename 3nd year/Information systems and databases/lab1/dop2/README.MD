
![iam-hungry](https://github.com/Denoske/ITMO-labs/blob/main/3nd%20year/Information%20systems%20and%20databases/lab1/dop2/model.jpg)


# Запросы:

1. Вставка нового клиента в таблицу "Client":

INSERT INTO Client (id, first_name, last_name, phone_number, email)
VALUES (1, 'Иван', 'Иванов', '+7 (999) 123-45-67', 'ivanov@example.com');


2. Обновление информации о клиенте в таблице "Client":

UPDATE Client
SET phone_number = '+7 (999) 987-65-43'
WHERE id = 1;


3. Удаление клиента из таблицы "Client":

DELETE FROM Client
WHERE id = 1;


4. Выборка списка клиентов, которые записаны на услугу с идентификатором 2:

SELECT c.first_name, c.last_name
FROM Appointment a
JOIN Client c ON a.client_id = c.id
WHERE a.service_id = 2;
