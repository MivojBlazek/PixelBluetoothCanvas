import subprocess
import bluetooth

def generate_bluetooth_address():
    try:
        # Run hciconfig command to get the Bluetooth address
        output = subprocess.check_output(["hciconfig", "hci0"]).decode("utf-8")
        for line in output.splitlines():
            if "Address" in line:
                return line.split()[2]  # Return the Bluetooth address
    except Exception as e:
        print("Could not retrieve Bluetooth address:", e)
    return None

def start_bluetooth_server():
    # Create a Bluetooth socket
    server_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

    # Bind the socket to an address and port
    port = 1
    server_socket.bind(("", port))
    server_socket.listen(1)

    print("Bluetooth server started. Waiting for a connection on RFCOMM channel", port)
    print("Server Bluetooth Address:", generate_bluetooth_address())

    while True:
        try:
            # Wait for a client to connect
            client_socket, address = server_socket.accept()
            print("Accepted connection from", address)

            while True:
                data = client_socket.recv(1024)  # Receive up to 1024 bytes
                if not data:
                    print("No data received. Closing connection.")
                    break
                print("Received data:", data.decode('utf-8'))  # Decode and print the data

                # Here, you can integrate your server logic to process the received data
                # For example, you can save it to a database or perform specific actions based on the data

        except OSError:
            print("Connection error. Closing the server.")
            break
        except Exception as e:
            print("An error occurred:", e)

        finally:
            client_socket.close()
            print("Connection closed.")

    server_socket.close()
    print("Bluetooth server closed.")

if __name__ == "__main__":
    start_bluetooth_server()
