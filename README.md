# Food Service System

## Project Summary
A C++ project demonstrating OOP and DSA concepts. The system allows customers to create accounts, select restaurants, and place orders. It uses Dijkstra’s algorithm to find the shortest route between the customer and the restaurant.

## Key Features
- **Account Management**: Customers can create accounts with encrypted passwords.
- **Order Placement**: Customers can select restaurants and place orders, which are stored in individual files.
- **Shortest Route Calculation**: Uses Dijkstra’s algorithm to determine the quickest path for delivery.

## Technical Highlights
- **Language**: C++
- **Encryption**: Shift Cipher for password security.
- **Algorithm**: Dijkstra’s algorithm for route optimization.
- **Data Storage**: Customer and order details stored in text files.

## File Descriptions
- **`FoodServiceSys.cpp`**: Main program file containing the implementation of the system.
- **`graph.txt`**: Stores location and distance data used by Dijkstra’s algorithm.
- **`James.txt`, `Jay.txt`**: Customer account details, including name, ID, and encrypted password.
- **`James_order.txt`, `Jay_order.txt`**: Order histories, including restaurant name, dish, quantity, and user location.

## How to Run
1. Compile `FoodServiceSys.cpp` using a C++ compiler.
2. Run the executable generated.
3. Follow the prompts to create accounts, place orders, and calculate the shortest route.

## Future Improvements
- Implement a more secure encryption algorithm.
- Add more restaurants and a dynamic menu system.
- Integrate real-time order tracking.
