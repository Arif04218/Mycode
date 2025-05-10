from flask import Flask, render_template, request
import numpy as np

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/calculate', methods=['POST'])
def calculate():
    rows = int(request.form['rows'])
    cols = int(request.form['cols'])
    matrix_str = request.form['matrix']

    # Parsing string matriks menjadi matriks NumPy
    import json
    matrix = np.array(json.loads(matrix_str))


    # Hitung basis matriks
    basis = np.linalg.matrix_rank(matrix)

    # Hitung peringkat matriks
    rank = np.linalg.matrix_rank(matrix)


    return render_template('result.html', matrix=matrix, basis=basis, rank=rank)

if __name__ == '__main__':
    app.run(debug=True)