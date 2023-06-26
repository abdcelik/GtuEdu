from flask import Flask, render_template, request, session
import mysql.connector
import pandas as pd
from datetime import datetime
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key ='856523d2ef396969da4b4bed267adebae75b95972010e56f8df5a2aeb6a663e5'

mydb = mysql.connector.connect(
    host="localhost",
    user="root",
    password="A413429c",
    database="GTUProjectManagement"
)

mycursor = mydb.cursor()

@app.route('/')
def home():
    is_loged_in = 'password' in session
    return render_template('index.html', is_loged_in = is_loged_in)

@app.route('/tables')
def get_tables():
    tables = []

    mycursor.execute("SELECT * FROM activities")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM priority")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM project")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM task")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM taskclasses")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM team")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM teamproject")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM teamuserrole")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM tmroles")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM user")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM usertask")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    return render_template(
        'show_table.html',
        tables = tables
    )

@app.route('/register', methods=['GET', 'POST'])
def register():
    if 'password' in session:
        return render_template('index.html', is_loged_in = True)

    if request.method == 'POST':
        first_name = request.form['first_name']
        last_name = request.form['last_name']
        email = request.form['email']
        password = generate_password_hash(request.form['password'])
        created_at = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        mycursor.execute(f"SELECT * FROM User Where email='{email}'")
        exist = mycursor.fetchall()

        if exist :
            print('This email is already used')
        else:
            print('New Record')
            sql = "INSERT INTO User (first_name, last_name, email, password, created_at) VALUES (%s, %s, %s, %s, %s)"
            val = (first_name, last_name, email, password, created_at)
            mycursor.execute(sql, val)
            mydb.commit()

    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    is_loged_in = False
    if 'password' in session:
        print('Already Loged in')
        return render_template('index.html', is_loged_in=True)
    
    if request.method == 'POST':
        
        email = request.form['email']
        password = request.form['password']

        mycursor.execute(f"SELECT * FROM User Where email='{email}'")
        user = mycursor.fetchone()

        if user and check_password_hash(user[4], password):
            session['password'] = user[4]
            is_loged_in = True
            print('Login Success')
        else:
            print('Login Fail')

    if is_loged_in:
        return render_template('index.html', is_loged_in=is_loged_in)
    else:
        return render_template('login.html')

@app.route('/logout')
def logout():
    if not 'password' in session:
        return render_template('index.html', is_loged_in=True)

    print('Logout')
    session.pop('password', None)
    return render_template('login.html')

@app.route('/users')
def get_users():
    mycursor.execute("SELECT * FROM User")
    myresult = mycursor.fetchall()
    df = pd.DataFrame(myresult, columns=mycursor.column_names)

    return render_template(
        'show_table.html',
        tables = [df]
    )

@app.route('/views')
def get_views():
    tables = []

    mycursor.execute("SELECT * FROM current_tasks")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM the_users")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM task_class_priority")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM task_project")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    mycursor.execute("SELECT * FROM task_priority")
    myresult = mycursor.fetchall()
    tables.append(pd.DataFrame(myresult, columns=mycursor.column_names))

    return render_template(
        'show_table.html',
        tables = tables
    )

@app.route('/example_form', methods=['POST', 'GET'])
def get_example_form():
    if request.method == 'POST':
        print(request.form)
        print('POST')

    elif request.method == 'GET':
        print(request.form)
        print('GET')

    else:
        print('UNKNOWN')

    return render_template('example_form.html')


@app.route('/activities')
def show_activities():
    mycursor.execute("SELECT * FROM Activities")
    myresult = mycursor.fetchall()

    df = pd.DataFrame(myresult, columns=mycursor.column_names)

    return render_template(
        'show_table.html',
        tables = [df]
    )

@app.route('/add_task', methods=['GET', 'POST'])
def add_task():
    if request.method == 'POST':
        
        name = request.form['name']
        description = request.form['description']
        created_at = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        planned_end_date = request.form['planned_end_date']
        actual_end_date = None
        priority = request.form['priority']
        task_class = request.form['task_class']
        project = request.form['project']
        user = request.form['user']

        sql = "INSERT INTO Task (name, description, created_at, planned_end_date, priority_id, task_class_id, project_id) VALUES (%s, %s, %s, %s, %s, %s, %s)"
        val = (name, description, created_at, planned_end_date, priority, task_class, project)
        mycursor.execute(sql, val)
        mydb.commit()

        sql = "INSERT INTO UserTask (`task_id`, `user_id`) VALUES (%s, %s)"
        val = (mycursor.lastrowid, user)
        mycursor.execute(sql, val)
        mydb.commit()

    mycursor.execute("SELECT * FROM Priority")
    priorities = mycursor.fetchall()
    priority_ids = [i[0] for i in priorities]
    priorities = pd.DataFrame(priorities, columns=mycursor.column_names)
    
    mycursor.execute("SELECT * FROM TaskClasses")
    task_classes = mycursor.fetchall()
    task_class_ids = [i[0] for i in task_classes]
    task_classes = pd.DataFrame(task_classes, columns=mycursor.column_names)

    mycursor.execute("SELECT * FROM Project")
    projects = mycursor.fetchall()
    project_ids = [i[0] for i in projects]
    projects = pd.DataFrame(projects, columns=mycursor.column_names)


    mycursor.execute("SELECT * FROM User")
    users = mycursor.fetchall()
    user_ids = [i[0] for i in users]
    users = pd.DataFrame(users, columns=mycursor.column_names)

    return render_template(
        'add_task.html',

        priorities = priorities,
        priority_ids = priority_ids,
        
        task_classes = task_classes,
        task_class_ids = task_class_ids,

        projects = projects,
        project_ids = project_ids,

        users = users,
        user_ids = user_ids
    )


@app.route('/delete_user', methods=['GET', 'POST'])
def delete_user():
    if request.method == 'POST':
        user_id = request.form['user']

        mycursor.execute('SET FOREIGN_KEY_CHECKS=0')

        sql = f"DELETE FROM User WHERE (idUser={user_id})"
        mycursor.execute(sql)
        mydb.commit()

        mycursor.execute('SET FOREIGN_KEY_CHECKS=1')

    mycursor.execute("SELECT * FROM User")
    users = mycursor.fetchall()
    user_ids = [i[0] for i in users]
    users = pd.DataFrame(users, columns=mycursor.column_names)

    return render_template('delete_user.html', users=users, user_ids=user_ids)

@app.route('/update_password', methods=['GET', 'POST'])
def update_password():

    if request.method == 'POST':
        user_id = request.form['user']
        password = generate_password_hash(request.form['password'])

        mycursor.execute('SET FOREIGN_KEY_CHECKS=0')

        sql = f"UPDATE `GTUProjectManagement`.`User` SET `password` = '{password}' WHERE (`idUser` = '{user_id}')"
        mycursor.execute(sql)
        mydb.commit()

        mycursor.execute('SET FOREIGN_KEY_CHECKS=1')

    mycursor.execute("SELECT * FROM User")
    users = mycursor.fetchall()
    user_ids = [i[0] for i in users]
    users = pd.DataFrame(users, columns=mycursor.column_names)

    return render_template('update_password.html', users=users, user_ids=user_ids)

@app.route('/add_project', methods=['GET', 'POST'])
def add_project():

    if request.method == 'POST':
        name = request.form['name']
        description = request.form['description']
        start_date = request.form['start_date']
        end_date = request.form['end_date']

        sql = "INSERT INTO `GTUProjectManagement`.`Project` (`name`, `description`, `start_date`, `end_date`) VALUES (%s, %s, %s, %s)"
        val = (name, description, start_date, end_date)
        mycursor.execute(sql, val)
        mydb.commit()

    return render_template('add_project.html')

if __name__ == '__main__':
    app.run()