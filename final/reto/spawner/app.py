from flask import Flask, request, render_template, make_response, url_for
import pickledb
import time
import os
import subprocess
import re

app = Flask(__name__, template_folder='templates')
db = None
os.chdir("../server")

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/spawn/<email>')
def spawn_new(email):
    global db
    email_filtered = re.sub(r'[^a-zA-Z0-9]', '', email)
    os.environ["COMPOSE_PROJECT_NAME"] = email_filtered
    s = str(subprocess.check_output('docker ps', shell=True))
    if s.find(email_filtered) != -1:
        print(s)
        return "Container already exists"
    else:
        os.system("docker compose up -d --build")
        s = subprocess.check_output('docker port ' + email_filtered + "-nginx-1", shell=True)
        port = s.split(b':')[1].decode('utf-8')
        return port