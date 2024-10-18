from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/endpoint', methods=['POST'])
def handle_post():
    data = request.get_json()
    print(f"Received data: {data}")
    return jsonify({"message": "Data received successfully!"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)  # Listen on all interfaces (replace with your IP address)

