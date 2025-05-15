# Simple HTTP Server

This is my first C project, a simple HTTP server.
It was developed in a Linux environment.

## Project Structure

- `server.c`: Contains the socket implementation.
- `main.c`: Connects the C files together.

## How to Build

To build the project, run the following command:

```sh
make
```

## How to Run

To run the server, use the following command:

```sh
./http_server
```

In a separate terminal, you can use the following command to test the server:

```sh
curl -v http://localhost:8080
```

## Features

- Basic HTTP request handling
- It just returns "Pwat Pwat" if the request is a GET request

## Future Improvements

- This is basically a template that can be improved in many ways. It can be reused to create web applications, or DevOps tools.

## License

This project is licensed under the MIT License.
# http_server
