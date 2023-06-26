CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`Activities` (
  `idActivities` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `description` TEXT(255) NOT NULL,
  `created_at` VARCHAR(45) NULL,
  PRIMARY KEY (`idActivities`),
  UNIQUE INDEX `idActivities_UNIQUE` (`idActivities` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`Priority` (
  `idPriority` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `degree` INT NOT NULL,
  PRIMARY KEY (`idPriority`),
  UNIQUE INDEX `idPriority_UNIQUE` (`idPriority` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`TaskClasses` (
  `idTaskClasses` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `Description` TEXT(255) NOT NULL,
  PRIMARY KEY (`idTaskClasses`),
  UNIQUE INDEX `idTask_Classes_UNIQUE` (`idTaskClasses` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`Project` (
  `idProject` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `description` TEXT(255) NOT NULL,
  `start_date` DATETIME NULL,
  `end_date` DATETIME NULL,
  PRIMARY KEY (`idProject`),
  UNIQUE INDEX `idProject_UNIQUE` (`idProject` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`User` (
  `idUser` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(45) NOT NULL,
  `last_name` VARCHAR(45) NOT NULL,
  `email` VARCHAR(60) NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `created_at` DATETIME NOT NULL,
  `company_email` VARCHAR(60) NULL,
  PRIMARY KEY (`idUser`),
  UNIQUE INDEX `idUser_UNIQUE` (`idUser` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`TMRoles` (
  `idTMRoles` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `description` TEXT(255) NOT NULL,
  PRIMARY KEY (`idTMRoles`),
  UNIQUE INDEX `idTMRoles_UNIQUE` (`idTMRoles` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`Team` (
  `idTeam` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `created_at` DATETIME NOT NULL,
  PRIMARY KEY (`idTeam`),
  UNIQUE INDEX `idtable1_UNIQUE` (`idTeam` ASC) VISIBLE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`Task` (
  `idTask` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `description` TEXT(255) NOT NULL,
  `created_at` DATETIME NOT NULL,
  `planned_end_date` DATETIME NOT NULL,
  `actual_end_date` DATETIME NULL,
  `priority_id` INT UNSIGNED NOT NULL,
  `task_class_id` INT UNSIGNED NOT NULL,
  `project_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idTask`),
  UNIQUE INDEX `idTask_UNIQUE` (`idTask` ASC) VISIBLE,
  CONSTRAINT `fk_Task_1`
    FOREIGN KEY (`priority_id`)
    REFERENCES `GTUProjectManagement`.`Priority` (`idPriority`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Task_2`
    FOREIGN KEY (`task_class_id`)
    REFERENCES `GTUProjectManagement`.`TaskClasses` (`idTaskClasses`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Task_3`
    FOREIGN KEY (`project_id`)
    REFERENCES `GTUProjectManagement`.`Project` (`idProject`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`TeamProject` (
  `idTeamProject` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `project_id` INT UNSIGNED NOT NULL,
  `team_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idTeamProject`),
  UNIQUE INDEX `idTeamProject_UNIQUE` (`idTeamProject` ASC) VISIBLE,
  CONSTRAINT `fk_TeamProject_1`
    FOREIGN KEY (`project_id`)
    REFERENCES `GTUProjectManagement`.`Project` (`idProject`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_TeamProject_2`
    FOREIGN KEY (`team_id`)
    REFERENCES `GTUProjectManagement`.`Team` (`idTeam`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`UserTask` (
  `idUserTask` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `task_id` INT UNSIGNED NOT NULL,
  `user_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idUserTask`),
  UNIQUE INDEX `idUserTask_UNIQUE` (`idUserTask` ASC) VISIBLE,
  CONSTRAINT `fk_UserTask_1`
    FOREIGN KEY (`user_id`)
    REFERENCES `GTUProjectManagement`.`User` (`idUser`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_UserTask_2`
    FOREIGN KEY (`task_id`)
    REFERENCES `GTUProjectManagement`.`Task` (`idTask`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `GTUProjectManagement`.`TeamUserRole` (
  `idTeamUserRole` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT UNSIGNED NOT NULL,
  `team_id` INT UNSIGNED NOT NULL,
  `role_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idTeamUserRole`),
  UNIQUE INDEX `idTeamUserRole_UNIQUE` (`idTeamUserRole` ASC) VISIBLE,
  CONSTRAINT `fk_TeamUserRole_1`
    FOREIGN KEY (`user_id`)
    REFERENCES `GTUProjectManagement`.`User` (`idUser`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_TeamUserRole_2`
    FOREIGN KEY (`team_id`)
    REFERENCES `GTUProjectManagement`.`Team` (`idTeam`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_TeamUserRole_3`
    FOREIGN KEY (`role_id`)
    REFERENCES `GTUProjectManagement`.`TMRoles` (`idTMRoles`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;