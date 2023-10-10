CREATE TABLE Client (
    id INT PRIMARY KEY,
    first_name VARCHAR(255),
    last_name VARCHAR(255),
    phone_number VARCHAR(20),
    email VARCHAR(255)
);

CREATE TABLE Staff (
    id INT PRIMARY KEY,
    first_name VARCHAR(255),
    last_name VARCHAR(255),
    position VARCHAR(255),
    salary DECIMAL(8, 2)
);

CREATE TABLE ServiceType (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    description TEXT
);

CREATE TABLE Service (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    price DECIMAL(8, 2),
    type_id INT,
    FOREIGN KEY (type_id) REFERENCES ServiceType(id)
);

CREATE TABLE Appointment (
    id INT PRIMARY KEY,
    date DATE,
    time TIME,
    client_id INT,
    staff_id INT,
    service_id INT,
    FOREIGN KEY (client_id) REFERENCES Client(id),
    FOREIGN KEY (staff_id) REFERENCES Staff(id),
    FOREIGN KEY (service_id) REFERENCES Service(id)
);

CREATE TABLE Product (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    price DECIMAL(8, 2),
    stock INT
);

CREATE TABLE Supplier (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20),
    address VARCHAR(255)
);

CREATE TABLE SupplierOrder (
    id INT PRIMARY KEY,
    supplier_id INT,
    product_id INT,
    quantity INT,
    order_date DATE,
    FOREIGN KEY (supplier_id) REFERENCES Supplier(id),
    FOREIGN KEY (product_id) REFERENCES Product(id)
);

CREATE TABLE ClientAppointment (
    client_id INT,
    appointment_id INT,
    PRIMARY KEY (client_id, appointment_id),
    FOREIGN KEY (client_id) REFERENCES Client(id),
    FOREIGN KEY (appointment_id) REFERENCES Appointment(id)
);

CREATE TABLE StaffAppointment (
    staff_id INT,
    appointment_id INT,
    PRIMARY KEY (staff_id, appointment_id),
    FOREIGN KEY (staff_id) REFERENCES Staff(id),
    FOREIGN KEY (appointment_id) REFERENCES Appointment(id)
);

CREATE TABLE ProductAppointment (
    product_id INT,
    appointment_id INT,
    PRIMARY KEY (product_id, appointment_id),
    FOREIGN KEY (product_id) REFERENCES Product(id),
    FOREIGN KEY (appointment_id) REFERENCES Appointment(id)
);

ALTER TABLE Staff
ADD COLUMN photo BLOB;
