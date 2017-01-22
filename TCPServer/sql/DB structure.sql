CREATE TABLE `Logger` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
)
ENGINE = INNODB



CREATE TABLE `State` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  CONSTRAINT `FK_state_id_logger` FOREIGN KEY (`id_logger`)
  REFERENCES `Logger` (`id`) ON DELETE NO ACTION ON UPDATE RESTRICT
)
ENGINE = INNODB



CREATE TRIGGER `InsertStateForLogRow`
	AFTER INSERT
	ON `Logger`
	FOR EACH ROW
BEGIN
  INSERT INTO `State` (`id_logger`) VALUES
    (`new`.`id`);
END;
