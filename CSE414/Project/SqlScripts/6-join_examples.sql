/* OUTER RIGHT JOIN */
SELECT * FROM Priority RIGHT OUTER JOIN Task ON Priority.idPriority = Task.priority_id;

/* OUTER LEFT JOIN */
SELECT * FROM TaskClasses LEFT OUTER JOIN Task ON TaskClasses.idTaskClasses = Task.priority_id;

/* FULL OUTER JOIN */
SELECT * FROM Project FULL JOIN Task;
