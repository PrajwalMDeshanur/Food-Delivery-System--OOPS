# Food Delivery Service System

## 📄 Overview
The **Food Delivery Service System** is a comprehensive application designed to manage food delivery operations. It allows users to register, place orders, and track them, while restaurant owners can manage their restaurant profiles, add menu items, and view orders. The system demonstrates robust use of Object-Oriented Programming (OOP) concepts, including inheritance, polymorphism, encapsulation, and abstraction.

## ✨ Features
### User Management
- **User Registration & Login**: Users can register by providing their details and login using their credentials.
- **Profile Management**: Users can view their profile details such as name, contact, email, and location.
- **Order Placement**: Users can place orders from a restaurant of their choice.
- **Order Tracking**: Users can track the status of their placed orders.
- **Order History**: Users can view a history of all their previous orders.

### Restaurant Owner Management
- **Owner Registration & Login**: Restaurant owners can register and login to manage their restaurant details.
- **Restaurant Profile Management**: Owners can view and update their restaurant profile.
- **Menu Management**: Owners can add and manage menu items for their restaurant.
- **Order Management**: Owners can view all orders placed for their restaurant.

### System Features
- **Role-Based Access**: Separate interfaces and functionalities for users and restaurant owners.
- **Data Encapsulation**: Secure handling of sensitive data such as passwords using getter and setter methods.
- **Graph-Based Routing (Future Scope)**: Implementing shortest path algorithms for efficient delivery routing.

## 🛠️ Technical Details
### Project Structure
- **Person Class**: Base class with common attributes for both `User` and `RestaurantOwner` classes.
- **User Class**: Inherits from `Person` and implements `UserActions` and `OrderActions` interfaces for user-specific functionalities.
- **RestaurantOwner Class**: Inherits from `Person` and implements `UserActions` interface for restaurant owner-specific functionalities.
- **FoodDeliveryService Class**: Manages the entire system, providing interfaces for user registration, login, and main system operations.

### Key Concepts
- **Inheritance and Polymorphism**: Implemented through the `Person` base class and derived `User` and `RestaurantOwner` classes.
- **Abstract Classes and Interfaces**: `UserActions` and `OrderActions` abstract classes enforce a structure for user and order-related actions.
- **Encapsulation**: Sensitive data is stored in private members and accessed through getters and setters, ensuring data security and integrity.
- **File I/O**: User and restaurant data are stored and managed using file operations.
