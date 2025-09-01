# Simple HTTP Server

The obligatory systems project, a simple HTTP server written in C.
It was developed in a Linux environment, therefore uses POSIX sockets for network operations.

## Project Structure

- `src/server.c`: Contains the socket implementation.
- `src/html_file.c`: A separate program to read / free HTML files from memory.
- `src/mime_types.c`: Using the `magic.h` library, this file allows the server to output the correct type of content of a file.
- `src/main.c`: Connects the C files together.

- `run_server.sh`: A simple Bash script wrapper to load files into the server.
- `public/`: A folder containing a simple HTML / CSS / JS example website. Feel free to replace it with your own files.

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

```bash
bash run_server.sh public/test.html
```

In a separate terminal, you can use the following command to test the server:

```sh
curl -v http://localhost:8080
```

Or open your browser with the address `http://localhost:8080`.

## Features

- Basic HTTP request handling
- It will simply serve your HTML file on `localhost:8080`, nothing more, nothing less


## License

This project is licensed under the AGPL-3.0 license.
