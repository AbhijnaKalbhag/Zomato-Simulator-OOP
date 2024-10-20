#include <bits/stdc++.h>
#include "oops_final.h"
using namespace std;

struct PairHash
{
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &p) const
    {
        auto hash1 = std::hash<T>{}(p.first);
        auto hash2 = std::hash<U>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Person
{
public:
    string Name;
    int age;
    string phone_no;

public:
    Person()
    {
        Name = " ";
        age = 0;
        phone_no = " ";
    }
    Person(string name, int age, string phone_no)
    {
        this->Name = name;
        this->age = age;
        this->phone_no = phone_no;
    }
    virtual void get_details() = 0;
    virtual void display_details() = 0;
};

class User : public Person
{
public:
    string username;
    string password;
    string address;

public:
    User() {}
    void get_details()
    {
        cout << "-------------------" << endl;
        cout << "enter user details:" << endl;
        cout << "Enter name:" << endl;
        cin >> Name;
        cout << "Enter Age:" << endl;
        cin >> age;
        cout << "Enter Phone number:" << endl;
        cin >> phone_no;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        cout << "-------------------" << endl;
    }
    void display_details()
    {
        cout << "------------------" << endl;
        cout << "User Details:\n";
        cout << "Name: " << Name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone number: " << phone_no << endl;
        cout << "Address: " << address << endl;
        cout << "------------------" << endl;
    }
};

class delivery_person : public Person
{
public:
    string vehicle_no;
    int availability = 1;

    delivery_person(string vehical_no, string name, int age)
    {
        this->vehicle_no = vehical_no;
        this->Name = name;
        this->age = age;
    }
    void get_details()
    {
        cout << "Enter name:" << endl;
        cin >> Name;
        cout << "Enter Age:" << endl;
        cin >> age;
        cout << "Enter Phone number:" << endl;
        cin >> phone_no;
    }
    void display_details()
    {
        cout << "------------------" << endl;
        cout << "Delivery person Details:\n";
        cout << "Name: " << Name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone number: " << phone_no << endl;
        cout << "------------------" << endl;
    }
};

template <typename RatingType, typename CommentType>
class Review
{
public:
    RatingType rating;
    CommentType comments;

    Review()
    {
        rating = RatingType();
        comments = CommentType();
    }

    Review(RatingType rating, CommentType comments)
    {
        this->rating = rating;
        this->comments = comments;
    }

    void rateItem()
    {
        std::cout << "Enter the rating (0.0 - 5.0): ";
        std::cin >> rating;
    }

    void addComments()
    {
        std::cout << "Enter your comments: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
    }

    void displayReview()
    {
        std::cout << "Rating: " << rating << std::endl;
        std::cout << "Comments: " << comments << std::endl;
    }
};

class Restaurant
{
public:
    string restaurant_name;
    string restaurant_location;
    unordered_map<string, float> menu;
    Review<float, std::string> restaurant_review;

public:
    Restaurant() {}
    Restaurant(string name, string location, unordered_map<string, float> menu)
    {
        restaurant_name = name;
        restaurant_location = location;
        this->menu = menu;
    }
    void display_menu()
    {
        cout << "-~-~-~-~-~-~-~-~-~-~-~" << endl;
        cout << "Menu for " << restaurant_name << ":\n";
        for (const auto &item : menu)
        {
            cout << item.first << " - Price: " << item.second << endl;
        }
        cout << "-~-~-~-~-~-~-~-~-~-~-~" << endl;
    }
    float item_cost(string item)
    {
        if (menu.find(item) != menu.end())
        {
            return menu[item];
        }
        return 0.0;
    }
    void rateRestaurant()
    {
        cout << "------------------" << endl;
        restaurant_review.rateItem();
        restaurant_review.addComments();

        std::cout << "Thank you for rating " << restaurant_name << "!" << std::endl;
        cout << "------------------" << endl;
    }

    void displayReview()
    {
        std::cout << "Review for " << restaurant_name << ":" << std::endl;
        restaurant_review.displayReview();
    }
};
class Payment
{
public:
    string mode;
    float amount;
    float tax = 0.16;
    int payment_id;

public:
    Payment() {}

    Payment(string mode, float amount)
    {
        this->mode = mode;
        this->amount = amount;
    }

    float generate_bill(std::unordered_map<std::pair<std::string, float>, int, PairHash> &items, float amount, float tax, string mode)
    {
        float total_amount = amount + (amount * tax);
        cout << "Total amount: " << total_amount << " (including tax)" << endl;
        cout << "Payment mode: " << mode << endl;

        cout << "Bill Details:" << endl;
        cout << "------------------" << endl;
        cout << "item\tcost\tquantity" << endl;
        for (const auto &food : items)
        {
            const auto &food_item = food.first;
            int quantity = food.second;

            cout << food_item.first << "\t" << food_item.second << "Rs\t" << quantity << endl;
        }
        cout << "------------------" << endl;
        return total_amount;
    }
};

class Order
{
public:
    int order_id;
    int quantity;
    Payment pay;
    Restaurant *restaurant_ord;
    float total_cost;
    unordered_map<std::pair<std::string, float>, int, PairHash> ordered;

public:
    Order() {}

    void Order_items(Restaurant &restaurant)
    {

        restaurant_ord = &restaurant;
        cout << "enter number of items:(quantity of each considered later)" << endl;
        cin >> quantity;

        cout << "here" << endl;
        for (int i = 0; i < quantity; i++)
        {
            string food;
            int count;
            float cost;

            cout << "Enter item name: ";
            cin>>food;
            cout << "Enter quantity: ";
            cin >> count;

            cost = restaurant.item_cost(food);
            if (cost == 0.0)
            {
                cout << "Item not found in the menu. Please try again." << endl;
                i--;
                continue;
            }
            total_cost += (cost * count);
            ordered[{food, cost}] = count;
        }
        pay.amount = total_cost;
    }
    void order_details()
    {
        cout << "Quantity: " << quantity << endl;
        cout << "Restaurant Name: " << restaurant_ord->restaurant_name << endl;
        cout << "Restaurant Location: " << restaurant_ord->restaurant_location << endl;
        pay.amount=pay.generate_bill(ordered, total_cost, 0.17, pay.mode);
    }
    void pay_bill()
    {
        string mode;
        cout << "total cost: " << pay.amount << endl;
        ;
        cout << "enter mode of payment" << endl;
        cin >> pay.mode;
        cout << "Payment successfull!!" << endl;
        cout << "------------" << endl;
    }

    void clearOrder()
    {
        ordered.clear();
        total_cost = 0.0;
        quantity = 0;
    }
};
class RestaurantFactory {
public:
    virtual Restaurant* createRestaurant() = 0;
};

class KamatRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Burger", 100.0}, {"Pizza", 150}, {"Pasta", 200}};
        return new Restaurant("Kamat", "Vidyanagar", menu);
    }
};

class NikkiBakeStudioRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Bownie", 50.0}, {"Cheesecake", 110.0}, {"coffee", 50.0}};
        return new Restaurant("Nikki bake studio", "Gandhi Nagar", menu);
    }
};
class SagarRatnaRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Dosa", 80.0}, {"Idli", 60.0}, {"Vada", 40.0}};
        return new Restaurant("Sagar Ratna", "MG Road", menu);
    }
};

class PunjabiDhabaRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Butter Chicken", 220.0}, {"Naan", 30.0}, {"Dal Makhani", 150.0}};
        return new Restaurant("Punjabi Dhaba", "Jayanagar", menu);
    }
};

class ItalianoRistoranteRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Margherita Pizza", 180.0}, {"Pasta Carbonara", 220.0}, {"Tiramisu", 120.0}};
        return new Restaurant("Italiano Ristorante", "Koramangala", menu);
    }
};
class ThaiThymeRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Tom Yum Soup", 150.0}, {"Pad Thai", 180.0}, {"Green Curry", 200.0}};
        return new Restaurant("Thai Thyme", "Indiranagar", menu);
    }
};
class MexicanFiestaRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Tacos", 120.0}, {"Burritos", 150.0}, {"Churros", 80.0}};
        return new Restaurant("Mexican Fiesta", "Whitefield", menu);
    }
};
class SouthIndianDelightsRestaurantFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant() override {
        unordered_map<string, float> menu = {{"Rava Dosa", 100.0}, {"Pongal", 80.0}, {"Coconut Chutney", 40.0}};
        return new Restaurant("South Indian Delights", "HSR Layout", menu);
    }
};

class Zomato_App {
public:
    string email;
    User user;
    vector<delivery_person> delivery_people = {
        {"KA-30-2432", "Rajesh", 32},
        {"KA-31-4567", "Suresh", 28},
        {"KA-29-7890", "Anjali", 24},
        {"KA-32-1357", "Priya", 29},
        {"KA-28-2468", "Vijay", 35},
        {"KA-33-9753", "Arun", 31},
        {"KA-27-8642", "Kiran", 27},
        {"KA-34-4579", "Neha", 26},
        {"KA-26-1234", "Ramesh", 30},
        {"KA-35-1111", "Gita", 33}
    };
    Order order_food;
    Restaurant* selected_restaurant;
    vector<RestaurantFactory*> restaurantFactories;

public:
    Zomato_App() {
        restaurantFactories.push_back(new KamatRestaurantFactory());
        restaurantFactories.push_back(new NikkiBakeStudioRestaurantFactory());
        restaurantFactories.push_back(new SagarRatnaRestaurantFactory());
        restaurantFactories.push_back(new PunjabiDhabaRestaurantFactory());
        restaurantFactories.push_back(new ItalianoRistoranteRestaurantFactory());
        restaurantFactories.push_back(new ThaiThymeRestaurantFactory());
        restaurantFactories.push_back(new MexicanFiestaRestaurantFactory());
        restaurantFactories.push_back(new SouthIndianDelightsRestaurantFactory());
    }

    void login_user() {
        cout << "Welcome to Zomato!" << endl;
        cout << "enter username:" << endl;
        cin >> user.username;
        cout << "enter password:" << endl;
        cin >> user.password;
        cout << "enter email-id:" << endl;
        cin >> email;
        user.get_details();
    }

    void display_user() {
        user.display_details();
    }

    void order_fooditems() {
        cout << "Available restaurants are:" << endl;

        for (size_t i = 0; i < restaurantFactories.size(); i++) {
            cout << i + 1 << ". " << restaurantFactories[i]->createRestaurant()->restaurant_name << " (" << restaurantFactories[i]->createRestaurant()->restaurant_location << ")" << endl;
        }

        int restaurant_choice;
        cout << "Enter the restaurant number: ";
        cin >> restaurant_choice;

        try {
            if (restaurant_choice < 1 || restaurant_choice > restaurantFactories.size()) {
                throw std::invalid_argument("Invalid restaurant choice.");
            }

            selected_restaurant = restaurantFactories[restaurant_choice - 1]->createRestaurant();
            selected_restaurant->display_menu();
            order_food.Order_items(*selected_restaurant);
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void order_details() {
        cout << "Order Details:" << endl;
        if (selected_restaurant) {
            cout << "Restaurant Name: " << selected_restaurant->restaurant_name << endl;
            cout << "Restaurant Location: " << selected_restaurant->restaurant_location << endl;
            order_food.order_details();
        } else {
            cout << "No restaurant selected. Please place an order first." << endl;
        }
    }

    void confirm_order() {
        cout << user.username << " order confirmed!!" << endl;
    }

    void pay_bill() {
        cout << "Proceed for payment" << endl;
        order_food.pay_bill();
        order_food.clearOrder();
    }

    void assign_delivery_person() {
        srand(time(0));
        int random_index = rand() % delivery_people.size();
        while (delivery_people[random_index].availability == 0) {
            random_index = rand() % delivery_people.size();
        }
        cout << "Delivery person on the way:  \n";
        delivery_people[random_index].display_details();
        delivery_people[random_index].availability = 0;
        cout << "Order delivered!!" << endl;
    }

    void give_review() {
        cout << "------------" << endl;
        selected_restaurant->rateRestaurant();
        cout << "------------" << endl;
    }

    ~Zomato_App() {
        for (auto factory : restaurantFactories) {
            delete factory;
        }
    }
};


int main()
{
    Zomato_App zomatoApp;

    zomatoApp.login_user();
    cout << "Hello " << zomatoApp.user.username << "!" << endl;

    char choice;
    do
    {
        cout << "---------------------------------------------------------" << endl;
        cout << "1. Order Food" << endl;
        cout << "2. Display User Details" << endl;
        cout << "3. Order Details" << endl;
        cout << "4. Confirm Order" << endl;
        cout << "5. Pay Bill" << endl;
        cout << "6. Assign Delivery Person" << endl;
        cout << "7. Add Review" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            zomatoApp.order_fooditems();
            break;
        case '2':
            zomatoApp.display_user();
            break;
        case '3':
            zomatoApp.order_details();
            break;
        case '4':
            zomatoApp.confirm_order();
            break;
        case '5':
            zomatoApp.pay_bill();
            break;
        case '6':
            zomatoApp.assign_delivery_person();
            break;
        case '7':
            zomatoApp.give_review();
            break;
        case '0':
            cout << "Thank you for using Zomato! Have a great day!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != '0');

    return 0;
}



