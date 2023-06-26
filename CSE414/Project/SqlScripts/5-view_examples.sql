/* --- 1 --- */

DROP VIEW IF EXISTS current_tasks;
CREATE VIEW current_tasks AS SELECT name, description, created_at FROM Task HAVING NOW() > created_at;
SELECT * FROM current_tasks;

/* --- 2 --- */

DROP VIEW IF EXISTS the_users;
CREATE VIEW the_users AS SELECT first_name, last_name, created_at, company_email FROM User;
SELECT * FROM the_users;

/* --- 3 --- */

DROP VIEW IF EXISTS task_class_priority;
CREATE VIEW task_class_priority AS SELECT DISTINCT Task.name AS task_name, TaskClasses.name as class_name FROM TaskClasses LEFT OUTER JOIN Task ON TaskClasses.idTaskClasses = Task.priority_id;
SELECT * FROM task_class_priority;

/* --- 4 --- */

DROP VIEW IF EXISTS task_priority;
CREATE VIEW task_priority AS SELECT Priority.name AS priority_name, Task.name AS task_name FROM Priority RIGHT OUTER JOIN Task ON Priority.idPriority = Task.priority_id;
SELECT * FROM task_priority;

/* --- 5 --- */

DROP VIEW IF EXISTS task_project;
CREATE VIEW task_project AS SELECT first_name, last_name, company_email, Team.name as team_name FROM User FULL JOIN Team;
SELECT * FROM task_project;
