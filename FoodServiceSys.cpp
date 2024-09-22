#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <climits>
#include <cctype>
#include <regex>

using namespace std;

// Function to check if an email is valid
bool isValidEmail(const string& email) {
    regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, email_pattern);
}

// Function to shift cipher the password
string shiftCipher(string text, int shift) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += char(int(base + (c - base + shift) % 26));
        } else {
            result += c;
        }
    }
    return result;
}

class User {
public:
    string username;
    string password;
    string mobileNo;
    int location;
    string email;

    bool registerUser() {
        cout << "Enter username: ";
        cin >> username;

        // Email validation loop
        do {
            cout << "Enter email: ";
            cin >> email;
            if (!isValidEmail(email)) {
                cout << "Invalid email format. Please enter again." << endl;
            }
        } while (!isValidEmail(email));

        cout << "Enter password: ";
        cin >> password;
        cout << "Enter mobile number: ";
        cin >> mobileNo;
        cout << "Enter location (1-9): ";
        cin >> location;

        // Encrypt password using shift cipher
        password = shiftCipher(password, 3);

        // Save user details to file
        ofstream userFile(username + ".txt");
        if (userFile.is_open()) {
            userFile << username << "\n" << password << "\n" << mobileNo << "\n" << location << "\n" << email << endl;
            userFile.close();
            cout << "User registered successfully!" << endl;
            return true;
        } else {
            cout << "Unable to create user file!" << endl;
            return false;
        }
    }

    bool loginUser() {
        string enteredUsername, enteredPassword;
        cout << "Enter username: ";
        cin >> enteredUsername;
        cout << "Enter password: ";
        cin >> enteredPassword;

        ifstream userFile(enteredUsername + ".txt");
        if (userFile.is_open()) {
            string fileUsername, filePassword, locationStr;
            getline(userFile, fileUsername);
            getline(userFile, filePassword);
            getline(userFile, mobileNo);
            getline(userFile, locationStr);
            getline(userFile, email);

            // Convert location back to integer
            location = stoi(locationStr);

            // Encrypt entered password to compare
            enteredPassword = shiftCipher(enteredPassword, 3);

            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                cout << "Login successful!" << endl;
                username = fileUsername;  // Set the username for the session
                return true;
            } else {
                cout << "Incorrect username or password. Please try again." << endl;
            }

            userFile.close();
        } else {
            cout << "User not found. Please register first." << endl;
        }
        return false;
    }

    void displayUserDetails() {
        cout << "Username: " << username << endl;
        cout << "Mobile Number: " << mobileNo << endl;
        cout << "Location: " << location << endl;
        cout << "Email: " << email << endl;
    }

    void displayOrderHistory() {
        ifstream orderFile(username + "_order.txt");
        if (orderFile.is_open()) {
            string line;
            while (getline(orderFile, line)) {
                cout << line << endl;
            }
            orderFile.close();
        } else {
            cout << "No past orders found!" << endl;
        }
    }
};

class Restaurant {
public:
    string name;
    string dish;
    double price;
    int location;

    Restaurant(string name, string dish, double price, int location) 
        : name(name), dish(dish), price(price), location(location) {}

    void display() {
        cout << "Restaurant: " << name << endl;
        cout << "Dish: " << dish << " - Price: ₹" << price << endl;
        cout << "Location: " << location << endl;
    }
};

class FoodDeliveryService {
private:
    vector<Restaurant> restaurants;
    unordered_map<int, vector<pair<int, int>>> adjList;  // Adjacency list for graph

    void loadRestaurants() {
        ifstream file("restaurant.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, dish, priceStr, locationStr;
            getline(ss, name, ',');
            getline(ss, dish, ',');
            getline(ss, priceStr, ',');
            getline(ss, locationStr, ',');
            double price = stod(priceStr);
            int location = stoi(locationStr);
            restaurants.push_back(Restaurant(name, dish, price, location));
        }
    }

    void loadGraph() {
        ifstream file("graph.txt");
        int src, dest, weight;
        while (file >> src >> dest >> weight) {
            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight}); // Assuming undirected graph
        }
    }

    int dijkstra(int src, int dest) {
        unordered_map<int, int> dist;
        for (auto& pair : adjList) {
            dist[pair.first] = INT_MAX;
        }
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == dest) break;

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist[dest];
    }

public:
    FoodDeliveryService() {
        loadRestaurants();
        loadGraph();
    }

    void start() {
        User user;
        string input;
        int choice;

        do {
            cout << "1. New User" << endl;
            cout << "2. Existing User" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> input;

            // Validate if input is a number
            if (!isdigit(input[0])) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            choice = stoi(input);

            switch (choice) {
                case 1:
                    if (user.registerUser()) {
                        int k;
                        cout << "1. View Profile Details\n";
                        cout << "2. View Restaurants and Items\n";
                        cout << "3. Place Order\n";
                        cout << "4. View Past Orders\n";  // Added option for viewing past orders
                        cin >> input;

                        if (!isdigit(input[0])) {
                            cout << "Invalid choice. Please try again." << endl;
                            continue;
                        }

                        k = stoi(input);

                        if (k == 1)
                            user.displayUserDetails();
                        else if (k == 2)
                            displayRestaurants();
                        else if (k == 3) {
                            displayRestaurants();
                            placeOrder(user);
                        }
                        else if(k == 4) {
                            user.displayOrderHistory();  // View past orders
                        }
                    }
                    break;
                case 2:
                    if (user.loginUser()) {
                        int k;
                        cout << "1. View Profile Details\n";
                        cout << "2. View Restaurants and Items\n";
                        cout << "3. Place Order\n";
                        cout << "4. View Past Orders\n";  // Added option for viewing past orders
                        cin >> input;

                        if (!isdigit(input[0])) {
                            cout << "Invalid choice. Please try again." << endl;
                            continue;
                        }

                        k = stoi(input);

                        if (k == 1)
                            user.displayUserDetails();
                        else if (k == 2)
                            displayRestaurants();
                        else if (k == 3) {
                            displayRestaurants();
                            placeOrder(user);
                        }
                        else if(k == 4) {
                            user.displayOrderHistory();  // View past orders
                        }
                    }
                    break;
                case 3:
                    cout << "Exiting the program..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    void displayRestaurants() {
        cout << "\nAvailable Restaurants and Dishes:" << endl;
        for (Restaurant& restaurant : restaurants) {
            restaurant.display();
            cout << endl;
        }
    }

    void placeOrder(User& user) {
        string restaurantName, dish;
        int quantity;
        cout << "Enter restaurant name: ";
        cin.ignore();
        getline(cin, restaurantName);
        cout << "Enter dish name: ";
        getline(cin, dish);
        cout << "Enter quantity: ";
        cin >> quantity;

        int restaurantLocation = -1;
        double dishPrice = 0.0;
        for (Restaurant& restaurant : restaurants) {
            if (restaurant.name == restaurantName && restaurant.dish == dish) {
                restaurantLocation = restaurant.location;
                dishPrice = restaurant.price;
                break;
            }
        }

        if (restaurantLocation == -1) {
            cout << "Restaurant or dish not found!" << endl;
            return;
        }

        int distance = dijkstra(user.location, restaurantLocation);
        if (distance == INT_MAX) {
            cout << "No path found between your location and the restaurant." << endl;
            return;
        }

        double totalCost = dishPrice * quantity;
        double timeToReach = static_cast<double>(distance) / 2.0;  // Vehicle speed is 2 units/sec

        ofstream orderFile(user.username + "_order.txt", ios::app);  // Open in append mode
        if (orderFile.is_open()) {
            orderFile << "Restaurant: " << restaurantName << "\n";
            orderFile << "Dish: " << dish << "\n";
            orderFile << "Quantity: " << quantity << "\n";
            orderFile << "User Location: " << user.location << "\n";
            orderFile << "Restaurant Location: " << restaurantLocation << "\n";
            orderFile << "Distance: " << distance << " units\n";
            orderFile << "Total Cost: ₹" << totalCost << "\n";
            orderFile << "Estimated Delivery Time: " << timeToReach * 10 << " minutes\n";
            orderFile << "------------------------------------------\n"; // Optional separator
            orderFile.close();
            cout << "Order placed successfully!" << endl;
            cout << "Distance from your location to the restaurant is " << distance << " units." << endl;
            cout << "Total cost for the order is ₹" << totalCost << endl;
            cout << "Estimated delivery time is " << timeToReach * 10 << " minutes" << endl;
        } else {
            cout << "Unable to create or open order file!" << endl;
        }
    }
};

int main() {
    FoodDeliveryService service;
    service.start();
    return 0;
}
