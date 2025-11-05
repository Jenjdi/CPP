#include <iostream>
#include <string>
#include <vector>

class Room {
public:
    Room(int id, const std::string& type, bool available = true)
        : id(id), type(type), available(available) {}

    int getId() const { return id; }
    std::string getType() const { return type; }
    bool isAvailable() const { return available; }
    void setAvailability(bool available) { this->available = available; }
    void setType(const std::string& type) { this->type = type; }

private:
    int id;
    std::string type;
    bool available;
};

class Customer {
public:
    Customer(int id, const std::string& name, const std::string& phone, int roomId)
        : id(id), name(name), phone(phone), roomId(roomId) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    int getRoomId() const { return roomId; }

private:
    int id;
    std::string name;
    std::string phone;
    int roomId;
};

class HotelSystem {
public:
    HotelSystem() : adminUsername("admin"), adminPassword("password") {}

    bool login(const std::string& username, const std::string& password) {
        return (username == adminUsername && password == adminPassword);
    }

    bool addRoom(int id, const std::string& type) {
        rooms.push_back(new Room(id, type));
        return true;
    }

    bool removeRoom(int id) {
        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if ((*it)->getId() == id) {
                rooms.erase(it);
                return true;
            }
        }
        return false;
    }

    bool modifyRoom(int id, const std::string& newType) {
        for (Room* room : rooms) {
            if (room->getId() == id) {
                room->setType(newType);
                return true;
            }
        }
        return false;
    }

    Room* getRoom(int id) {
        for (Room* room : rooms) {
            if (room->getId() == id) {
                return room;
            }
        }
        return nullptr;
    }

    std::vector<Room*> getAllRooms() {
        return rooms;
    }

    bool addCustomer(int id, const std::string& name, const std::string& phone, int roomId) {
        customers.push_back(new Customer(id, name, phone, roomId));
        return true;
    }

    bool removeCustomer(int id) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if ((*it)->getId() == id) {
                customers.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<Customer*> getAllCustomers() {
        return customers;
    }

    bool bookRoom(int roomId, int customerId) {
        Room* room = getRoom(roomId);
        if (room && room->isAvailable()) {
            room->setAvailability(false);
            addCustomer(customerId, "Customer" + std::to_string(customerId), "Phone" + std::to_string(customerId), roomId);
            return true;
        }
        return false;
    }

    bool checkOutRoom(int roomId) {
        Room* room = getRoom(roomId);
        if (room) {
            room->setAvailability(true);
            for (auto it = customers.begin(); it != customers.end(); ++it) {
                if ((*it)->getRoomId() == roomId) {
                    customers.erase(it);
                    break;
                }
            }
            return true;
        }
        return false;
    }

private:
    std::vector<Room*> rooms;
    std::vector<Customer*> customers;
    std::string adminUsername;
    std::string adminPassword;
};

// 显示菜单
void showMenu() {
    std::cout << "\n--- 宾馆管理系统 ---\n";
    std::cout << "1. 客房信息管理\n";
    std::cout << "2. 客户信息管理\n";
    std::cout << "3. 定房\n";
    std::cout << "4. 退房\n";
    std::cout << "5. 退出\n";
    std::cout << "请选择: ";
}

// 管理房间
void manageRooms(HotelSystem& system) {
    int choice;
    do {
        std::cout << "\n1. 录入房间\n";
        std::cout << "2. 删除房间\n";
        std::cout << "3. 修改房间\n";
        std::cout << "4. 查询房间\n";
        std::cout << "5. 返回\n";
        std::cout << "请选择: ";
        std::cin >> choice;

        if (choice == 1) {
            int id;
            std::string type;
            std::cout << "请输入房间号: ";
            std::cin >> id;
            std::cout << "请输入房间类型: ";
            std::cin.ignore();
            std::getline(std::cin, type);
            system.addRoom(id, type);
        } else if (choice == 2) {
            int id;
            std::cout << "输入房间号以删除: ";
            std::cin >> id;
            system.removeRoom(id);
        } else if (choice == 3) {
            int id;
            std::string type;
            std::cout << "输入房间号以修改: ";
            std::cin >> id;
            std::cout << "输入新房间类型: ";
            std::cin.ignore();
            std::getline(std::cin, type);
            system.modifyRoom(id, type);
        } else if (choice == 4) {
            auto rooms = system.getAllRooms();
            for (Room* room : rooms) {
                std::cout << "房间号: " << room->getId() << ", 类型: " << room->getType() << ", 状态信息: " << (room->isAvailable() ? "可入住" : "不可入住") << "\n";
            }
        }
    } while (choice != 5);
}

// 管理客户
void manageCustomers(HotelSystem& system) {
    int choice;
    do {
        std::cout << "\n1. 添加客户\n";
        std::cout << "2. 删除客户\n";
        std::cout << "3. 查询客户\n";
        std::cout << "4. 返回\n";
        std::cout << "请选择: ";
        std::cin >> choice;

        if (choice == 1) {
            int id;
            std::string name, phone;
            int roomId;
            std::cout << "输入客户ID: ";
            std::cin >> id;
            std::cout << "输入客户姓名: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "输入客户电话号码: ";
            std::getline(std::cin, phone);
            std::cout << "输入房间号: ";
            std::cin >> roomId;
            system.addCustomer(id, name, phone, roomId);
        } else if (choice == 2) {
            int id;
            std::cout << "输入客户ID以删除: ";
            std::cin >> id;
            system.removeCustomer(id);
        } else if (choice == 3) {
            auto customers = system.getAllCustomers();
            for (Customer* customer : customers) {
                std::cout << "客户ID: " << customer->getId() << ", 姓名: " << customer->getName() << ", 电话: " << customer->getPhone() << ", 房间号: " << customer->getRoomId() << "\n";
            }
        }
    } while (choice != 4);
}

// 主程序
int main() {
    HotelSystem system;
    std::string username, password;
    
    // 登录
    std::cout << "输入用户名: ";
    std::cin >> username;
    std::cout << "输入密码: ";
    std::cin >> password;

    if (!system.login(username, password)) {
        std::cout << "非法用户!\n";
        return 1;
    }
    
    // 显示主菜单
    int choice;
    do {
        showMenu();
        std::cin >> choice;

        if (choice == 1) {
            manageRooms(system);
        } else if (choice == 2) {
            manageCustomers(system);
        } else if (choice == 3) {
            int roomId, customerId;
            std::cout << "输入房间号以预定: ";
            std::cin >> roomId;
            std::cout << "输入客户ID: ";
            std::cin >> customerId;
            if (system.bookRoom(roomId, customerId)) {
                std::cout << "房间预定成功!\n";
            } else {
                std::cout << "房间预定失败.\n";
            }
        } else if (choice == 4) {
            int roomId;
            std::cout << "输入房间号以退房: ";
            std::cin >> roomId;
            if (system.checkOutRoom(roomId)) {
                std::cout << "退房成功!\n";
            } else {
                std::cout << "退房失败.\n";
            }
        }
    } while (choice != 5);

    return 0;
}
