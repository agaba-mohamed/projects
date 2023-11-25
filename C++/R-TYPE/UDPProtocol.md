# UDP Protocol Documentation

This document provides information on the custom UDP-based protocol used to send packages. Each package follows the format "id: X x:X y:Y type:TYPE or id: X shoot".

## Package Structure

Each package consists of the following elements:

- **id:** A unique identifier for the package.
- **x:** The X-coordinate value.
- **y:** The Y-coordinate value.
- **type:** The type of the entity.

Example:
```
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

## Communication Flow

The UDP protocol operates with a simple communication flow. The client sends packages to the server, and the server may respond with acknowledgments or process the received packages based on the type.

## Usage

### Sending a Package

To send a package from the client to the server, follow this format:
```
id: <ID> x:<X> y:<Y> type:<TYPE>
id: <ID> shoot
```

- Replace `<ID>` with the unique package identifier.
- Replace `<X>` and `<Y>` with the X and Y coordinate values.
- Replace `<TYPE>` with the package type.

Example:
```
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

### Server Response

The server may respond with acknowledgments or process the received packages based on the type. The response format depends on the server's behavior.

## Error Handling

In the case of invalid or malformed packages, the UDP protocol may not provide extensive error handling. It's essential for both the client and server to handle errors and ensure that packages are correctly formatted.

## Security Considerations

Since UDP is a connectionless protocol, it does not provide the same level of security and reliability as TCP. It is important to implement additional security measures if needed, such as encryption or authentication.

## Examples

### Sending a Package (Client)
```plaintext
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

### Server Response (Sample Acknowledgment)
```plaintext
Received package: id: 123 x:42 y:64 type:DATA
Received package: id: 123 shoot
```

## Conclusion

This document outlines the structure and basic usage of the custom UDP protocol for sending packages. Ensure that packages are correctly formatted to ensure successful communication between the client and server.

Please note that this is a simplified example, and you can expand the documentation to include more details about your protocol, error handling, and specific server behavior based on package types and more.