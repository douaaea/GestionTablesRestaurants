-- Restaurant table
CREATE TABLE [dbo].[Restaurant] (
  idRestaurant INT PRIMARY KEY IDENTITY,
  nom VARCHAR(255) NOT NULL,
  adresse VARCHAR(255) NOT NULL,
  cuisine VARCHAR(255) NOT NULL
);

-- Tbla table 
CREATE TABLE [dbo].[Tbla] (
  idTbla INT PRIMARY KEY IDENTITY,
  capacite INT NOT NULL,
  idRestaurant INT,
  FOREIGN KEY (idRestaurant) REFERENCES Restaurant(idRestaurant)
  ON DELETE CASCADE
  ON UPDATE CASCADE
);

-- Reservation table
CREATE TABLE [dbo].[Reservation] (
  idReservation INT PRIMARY KEY IDENTITY,
  date DATE NOT NULL,
  heureArr FLOAT NOT NULL,
  heureDep FLOAT NOT NULL,
  nbrPersonne INT NOT NULL,
  idTbla INT,  -- Foreign key DE Tbla table
  FOREIGN KEY (idTbla) REFERENCES Tbla(idTbla)
  ON DELETE CASCADE
  ON UPDATE CASCADE
);

-- Client table
CREATE TABLE [dbo].[Client] (
  idClient INT PRIMARY KEY IDENTITY,
  nom VARCHAR(255) NOT NULL,
  email VARCHAR(255) NOT NULL
);

-- Admin table
CREATE TABLE [dbo].[Admin] (
  idAdmin INT PRIMARY KEY IDENTITY,
  nom VARCHAR(255) NOT NULL
);

-- Login table
CREATE TABLE [dbo].[Login] (
  idLogin INT PRIMARY KEY IDENTITY,
  username VARCHAR(255) NOT NULL,
  password VARCHAR(255) NOT NULL,
  idAdmin INT FOREIGN KEY REFERENCES Admin(idAdmin)
  ON DELETE CASCADE
  ON UPDATE CASCADE
);