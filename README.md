# Simple HTTP Server

The obligatory systems project, a simple HTTP server written in C.
It was developed in a Linux environment, therefore uses POSIX sockets for network operations.

## Project Structure

- `server.c`: Contains the socket implementation.
- `main.c`: Connects the C files together.

## How to Build

To build the project, run the following command:

```sh
make
```

You can delete compiled binaries with:

```sh
make clean
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

## Future Features

I am aiming for a "live server" equivalent and plan for additional features:

- Serving Static Files
  - Test if the server can serve files from a specified directory (e.g., HTML, CSS, and JavaScript files).
  - Verify that the server handles paths correctly (e.g., index.html for /).

- Error Pages
Verify that the server serves custom error pages (e.g., 404.html for not found errors).

- Cross-Browser Compatibility
Test the server's behavior with requests from different browsers or tools (e.g., curl, Postman, Chrome).


## License

This project is licensed under the AGPL-3.0 license.
