/* --- 1 --- */

DROP TRIGGER IF EXISTS `GTUProjectManagement`.`Task_AFTER_INSERT`;

DELIMITER $$
USE `GTUProjectManagement`$$
CREATE DEFINER = CURRENT_USER TRIGGER `GTUProjectManagement`.`Task_AFTER_INSERT` AFTER INSERT ON `Task` FOR EACH ROW
BEGIN
	INSERT INTO `GTUProjectManagement`.`Activities` (`description`) VALUES (CONCAT(NEW.name, " is a new task"));
END$$
DELIMITER ;

/* --- 2 --- */

DROP TRIGGER IF EXISTS `GTUProjectManagement`.`User_AFTER_INSERT`;

DELIMITER $$
USE `GTUProjectManagement`$$
CREATE DEFINER = CURRENT_USER TRIGGER `GTUProjectManagement`.`User_AFTER_INSERT` AFTER INSERT ON `User` FOR EACH ROW
BEGIN
	INSERT INTO `GTUProjectManagement`.`Activities` (`description`) VALUES (CONCAT(NEW.first_name, " is a new user"));
END$$
DELIMITER ;

/* --- 3 --- */

DROP TRIGGER IF EXISTS `GTUProjectManagement`.`Activities_BEFORE_INSERT`;

DELIMITER $$
USE `GTUProjectManagement`$$
CREATE DEFINER = CURRENT_USER TRIGGER `GTUProjectManagement`.`Activities_BEFORE_INSERT` BEFORE INSERT ON `Activities` FOR EACH ROW
BEGIN
	SET NEW.created_at = NOW();
END$$
DELIMITER ;

/* --- 4 --- */

DROP TRIGGER IF EXISTS `GTUProjectManagement`.`Project_BEFORE_INSERT`;

DELIMITER $$
USE `GTUProjectManagement`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `Project_BEFORE_INSERT` BEFORE INSERT ON `Project` FOR EACH ROW BEGIN
	DECLARE temp DATETIME;
    
    IF NEW.start_date IS NULL THEN
		SET NEW.start_date = NOW();
    END IF;

    IF  NEW.end_date IS NOT NULL AND NEW.start_date > NEW.end_date THEN
		SET temp = NEW.start_date;
		SET NEW.start_date = NEW.end_date;
		SET NEW.end_date = temp;
    END IF;
END$$
DELIMITER ;

/* --- 5 --- */

DROP TRIGGER IF EXISTS `GTUProjectManagement`.`User_BEFORE_INSERT`;

DELIMITER $$
USE `GTUProjectManagement`$$
CREATE DEFINER = CURRENT_USER TRIGGER `GTUProjectManagement`.`User_BEFORE_INSERT` BEFORE INSERT ON `User` FOR EACH ROW
BEGIN
	IF NEW.company_email IS NULL THEN
		IF NOT EXISTS(SELECT * FROM User WHERE first_name=NEW.first_name AND last_name=NEW.last_name) THEN
			SET NEW.company_email = CONCAT(NEW.first_name, NEW.last_name, "@mycompany.com");
		ELSE
			SET NEW.company_email = CONCAT(NEW.created_at, "@mycompany.com");
		END IF;
    END IF;
END$$
DELIMITER ;
