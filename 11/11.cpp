#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

struct Date {
    int day;
    int month;
    int year;

    bool isValid() const {
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap && month == 2) daysInMonth[1] = 29;

        return (day >= 1 && day <= daysInMonth[month - 1]);
    }

    void display() const {
        std::cout << (day < 10 ? "0" : "") << day << "."
            << (month < 10 ? "0" : "") << month << "."
            << year;
    }
};

struct Phone {
    int countryCode;
    int cityCode;
    long long number;

    void display() const {
        std::cout << "+" << countryCode << " (" << cityCode << ") " << number;
    }
};

enum class Group {
    WORK,
    FAMILY,
    FRIENDS,
    OTHERS
};

struct Contact {
    std::string surname;
    std::string name;
    std::string patronymic;
    Phone phone;
    Date birthday;
    std::string email;
    Group category;

    void display() const {
        std::cout << "==========================================\n";
        std::cout << "| ФИО: " << surname << " " << name << " " << patronymic << "\n";
        std::cout << "| Телефон: ";
        phone.display();
        std::cout << "\n";
        std::cout << "| Дата рождения: ";
        birthday.display();
        std::cout << "\n";
        std::cout << "| Email: " << email << "\n";
        std::cout << "| Категория: ";

        switch (category) {
        case Group::WORK: std::cout << "Работа"; break;
        case Group::FAMILY: std::cout << "Семья"; break;
        case Group::FRIENDS: std::cout << "Друзья"; break;
        case Group::OTHERS: std::cout << "Другое"; break;
        }
        std::cout << "\n";
        std::cout << "==========================================\n";
    }
};

// Функция для проверки корректности email
bool isValidEmail(const std::string& email) {
    if (email.empty()) return false;

    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) return false;

    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == email.length() - 1) return false;

    return true;
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n'); // Вместо numeric_limits
}

// Функция для ввода даты с проверкой
Date inputDate() {
    Date date;
    do {
        std::cout << "  Введите день (1-31): ";
        std::cin >> date.day;
        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка! Введите число.\n";
            continue;
        }

        std::cout << "  Введите месяц (1-12): ";
        std::cin >> date.month;
        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка! Введите число.\n";
            continue;
        }

        std::cout << "  Введите год (1900-2100): ";
        std::cin >> date.year;
        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка! Введите число.\n";
            continue;
        }

        if (!date.isValid()) {
            std::cout << "Ошибка! Неверная дата. Попробуйте снова.\n";
        }
        else {
            break;
        }

    } while (true);

    return date;
}

// Функция для ввода телефона с проверкой
Phone inputPhone() {
    Phone phone;
    std::cout << "  Введите код страны (например, 7): ";
    std::cin >> phone.countryCode;

    std::cout << "  Введите код города (например, 495): ";
    std::cin >> phone.cityCode;

    std::cout << "  Введите номер телефона (только цифры): ";
    std::cin >> phone.number;

    return phone;
}

// Функция для ввода категории
Group inputCategory() {
    int choice;
    do {
        std::cout << "Выберите категорию:\n";
        std::cout << "  1. Работа\n";
        std::cout << "  2. Семья\n";
        std::cout << "  3. Друзья\n";
        std::cout << "  4. Другое\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка! Введите число 1-4.\n";
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            break;
        }
        else {
            std::cout << "Ошибка! Введите число от 1 до 4.\n";
        }
    } while (true);

    switch (choice) {
    case 1: return Group::WORK;
    case 2: return Group::FAMILY;
    case 3: return Group::FRIENDS;
    default: return Group::OTHERS;
    }
}
// Функция для редактирования контакта
void editContact(Contact& contact) {
    int editChoice;

    do {
        std::cout << "\n========================================\n";
        std::cout << "         РЕДАКТИРОВАНИЕ КОНТАКТА\n";
        std::cout << "========================================\n\n";

        std::cout << "Текущие данные:\n";
        contact.display();

        std::cout << "\nЧто хотите изменить?\n";
        std::cout << "  1. Фамилию\n";
        std::cout << "  2. Имя\n";
        std::cout << "  3. Отчество\n";
        std::cout << "  4. Телефон\n";
        std::cout << "  5. Дату рождения\n";
        std::cout << "  6. Email\n";
        std::cout << "  7. Категорию\n";
        std::cout << "  8. Выйти из редактирования\n";
        std::cout << "Ваш выбор: ";

        std::cin >> editChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка! Введите число.\n";
            system("pause");
            system("cls");
            continue;
        }

        clearInputBuffer();
        system("cls");

        switch (editChoice) {
        case 1:
            std::cout << "Текущая фамилия: " << contact.surname << "\n";
            std::cout << "Введите новую фамилию: ";
            std::getline(std::cin, contact.surname);
            std::cout << "Фамилия обновлена!\n";
            break;

        case 2:
            std::cout << "Текущее имя: " << contact.name << "\n";
            std::cout << "Введите новое имя: ";
            std::getline(std::cin, contact.name);
            std::cout << "Имя обновлено!\n";
            break;

        case 3:
            std::cout << "Текущее отчество: " << contact.patronymic << "\n";
            std::cout << "Введите новое отчество: ";
            std::getline(std::cin, contact.patronymic);
            std::cout << "Отчество обновлено!\n";
            break;

        case 4:
            std::cout << "Текущий телефон: ";
            contact.phone.display();
            std::cout << "\n\n--- Введите новый номер телефона ---\n";
            contact.phone = inputPhone();
            std::cout << "Телефон обновлен!\n";
            break;

        case 5:
            std::cout << "Текущая дата рождения: ";
            contact.birthday.display();
            std::cout << "\n\n--- Введите новую дату рождения ---\n";
            contact.birthday = inputDate();
            std::cout << "Дата рождения обновлена!\n";
            break;

        case 6:
            std::cout << "Текущий email: " << contact.email << "\n";
            do {
                std::cout << "Введите новый email: ";
                std::getline(std::cin, contact.email);

                if (!isValidEmail(contact.email)) {
                    std::cout << "Ошибка! Неверный формат email (пример: name@domain.com)\n";
                }
                else {
                    std::cout << "Email обновлен!\n";
                    break;
                }
            } while (true);
            break;

        case 7:
            std::cout << "Текущая категория: ";
            switch (contact.category) {
            case Group::WORK: std::cout << "Работа"; break;
            case Group::FAMILY: std::cout << "Семья"; break;
            case Group::FRIENDS: std::cout << "Друзья"; break;
            case Group::OTHERS: std::cout << "Другое"; break;
            }
            std::cout << "\n\n";
            contact.category = inputCategory();
            std::cout << "Категория обновлена!\n";
            break;

        case 8:
            std::cout << "Выход из редактирования...\n";
            break;

        default:
            std::cout << "Ошибка! Неверный выбор. Введите число от 1 до 8.\n";
            break;
        }

        if (editChoice != 8) {
            std::cout << "\n\nНажмите Enter для продолжения...";
            clearInputBuffer();
            std::cin.get();
            system("cls");
        }

    } while (editChoice != 8);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "Russian");

    std::vector<Contact> contacts;
    int choice;

    do {
        std::cout << "____________________________________\n";
        std::cout << "|                                  |\n";
        std::cout << "|            РЕГИСТРАЦИЯ           |\n";
        std::cout << "|__________________________________|\n";
        std::cout << "|                                  |\n";
        std::cout << "|      1. Добавление контакта      |\n";
        std::cout << "|__________________________________|\n";
        std::cout << "|                                  |\n";
        std::cout << "|      2. Просмотр всех записей    |\n";
        std::cout << "|__________________________________|\n";
        std::cout << "|                                  |\n";
        std::cout << "|      3. Выход                    |\n";
        std::cout << "|__________________________________|\n";
        std::cout << "|                                  |\n";
        std::cout << "|    Выберите действие (1-3):      |\n";
        std::cout << "|__________________________________|\n";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "\nОшибка! Введите число.\n";
            system("pause");
            system("cls");
            continue;
        }

        system("cls");

        switch (choice)
        {
        case 1: {
            Contact newContact;

            clearInputBuffer();

            std::cout << "========================================\n";
            std::cout << "         ДОБАВЛЕНИЕ КОНТАКТА\n";
            std::cout << "========================================\n\n";

            std::cout << "Введите фамилию: ";
            std::getline(std::cin, newContact.surname);

            std::cout << "Введите имя: ";
            std::getline(std::cin, newContact.name);

            std::cout << "Введите отчество: ";
            std::getline(std::cin, newContact.patronymic);

            std::cout << "\n--- Введите номер телефона ---\n";
            newContact.phone = inputPhone();

            std::cout << "\n--- Введите дату рождения ---\n";
            newContact.birthday = inputDate();

            clearInputBuffer();

            do {
                std::cout << "\nВведите email: ";
                std::getline(std::cin, newContact.email);

                if (!isValidEmail(newContact.email)) {
                    std::cout << "Ошибка! Неверный формат email (пример: name@domain.com)\n";
                }
                else {
                    break;
                }
            } while (true);

            std::cout << "\n";
            newContact.category = inputCategory();

            contacts.push_back(newContact);

            std::cout << "\n*** Контакт успешно добавлен! ***\n";
            std::cout << "Всего контактов в книге: " << contacts.size() << "\n";
            break;
        }

        case 2: {
            std::cout << "========================================\n";
            std::cout << "        ПРОСМОТР ВСЕХ ЗАПИСЕЙ\n";
            std::cout << "========================================\n\n";

            if (contacts.empty()) {
                std::cout << "Список контактов пуст.\n";
                std::cout << "Всего записей: 0\n";
            }
            else {
                std::cout << "Всего записей: " << contacts.size() << "\n\n";

                for (size_t i = 0; i < contacts.size(); ++i) {
                    std::cout << "Контакт #" << (i + 1) << ":\n";
                    contacts[i].display();
                    std::cout << "\n";
                }

                // Меню действий с контактами
                int actionChoice;
                do {
                    std::cout << " __________________________________ \n";
                    std::cout << "|                                  |\n";
                    std::cout << "|      1. Сортировка               |\n";
                    std::cout << "|__________________________________|\n";
                    std::cout << "|                                  |\n";
                    std::cout << "|      2. Редактирование           |\n";
                    std::cout << "|__________________________________|\n";
                    std::cout << "|                                  |\n";
                    std::cout << "|      3. Удаление                 |\n";
                    std::cout << "|__________________________________|\n";
                    std::cout << "|                                  |\n";
                    std::cout << "|      4. Назад в главное меню     |\n";
                    std::cout << "|__________________________________|\n";
                    std::cout << "Ваш выбор: ";

                    std::cin >> actionChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        clearInputBuffer();
                        std::cout << "Ошибка! Введите число.\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    clearInputBuffer();
                    system("cls");

                    switch (actionChoice) {
                    case 1: {
                        // Сортировка
                        int sortChoice;
                        std::cout << "Сортировка по:\n";
                        std::cout << "  1. Фамилии\n";
                        std::cout << "  2. Имени\n";
                        std::cout << "  3. Дате рождения\n";
                        std::cout << "Ваш выбор: ";
                        std::cin >> sortChoice;

                        if (sortChoice == 1) {
                            std::sort(contacts.begin(), contacts.end(),
                                [](const Contact& a, const Contact& b) {
                                    return a.surname < b.surname;
                                });
                            std::cout << "Контакты отсортированы по фамилии!\n";
                        }
                        else if (sortChoice == 2) {
                            std::sort(contacts.begin(), contacts.end(),
                                [](const Contact& a, const Contact& b) {
                                    return a.name < b.name;
                                });
                            std::cout << "Контакты отсортированы по имени!\n";
                        }
                        else if (sortChoice == 3) {
                            std::sort(contacts.begin(), contacts.end(),
                                [](const Contact& a, const Contact& b) {
                                    if (a.birthday.year != b.birthday.year)
                                        return a.birthday.year < b.birthday.year;
                                    if (a.birthday.month != b.birthday.month)
                                        return a.birthday.month < b.birthday.month;
                                    return a.birthday.day < b.birthday.day;
                                });
                            std::cout << "Контакты отсортированы по дате рождения!\n";
                        }
                        break;
                    }

                    case 2: {
                        // Редактирование
                        if (contacts.empty()) {
                            std::cout << "Нет контактов для редактирования!\n";
                            break;
                        }

                        int contactNum;
                        std::cout << "Введите номер контакта для редактирования (1-" << contacts.size() << "): ";
                        std::cin >> contactNum;

                        if (std::cin.fail() || contactNum < 1 || contactNum > static_cast<int>(contacts.size())) {
                            std::cin.clear();
                            clearInputBuffer();
                            std::cout << "Ошибка! Неверный номер контакта.\n";
                        }
                        else {
                            editContact(contacts[contactNum - 1]);
                            std::cout << "Редактирование завершено!\n";
                        }
                        break;
                    }

                    case 3: {
                        // Удаление
                        if (contacts.empty()) {
                            std::cout << "Нет контактов для удаления!\n";
                            break;
                        }

                        int contactNum;
                        std::cout << "Введите номер контакта для удаления (1-" << contacts.size() << "): ";
                        std::cin >> contactNum;

                        if (std::cin.fail() || contactNum < 1 || contactNum > static_cast<int>(contacts.size())) {
                            std::cin.clear();
                            clearInputBuffer();
                            std::cout << "Ошибка! Неверный номер контакта.\n";
                        }
                        else {
                            char confirm;
                            std::cout << "Вы уверены, что хотите удалить контакт? (y/n): ";
                            std::cin >> confirm;

                            if (confirm == 'y' || confirm == 'Y') {
                                contacts.erase(contacts.begin() + (contactNum - 1));
                                std::cout << "Контакт успешно удален!\n";
                                std::cout << "Осталось контактов: " << contacts.size() << "\n";
                            }
                            else {
                                std::cout << "Удаление отменено.\n";
                            }
                        }
                        break;
                    }

                    case 4:
                        std::cout << "Возврат в главное меню...\n";
                        break;

                    default:
                        std::cout << "Ошибка! Неверный выбор.\n";
                        break;
                    }

                    if (actionChoice != 4) {
                        std::cout << "\n\nНажмите Enter для продолжения...";
                        clearInputBuffer();
                        std::cin.get();
                        system("cls");

                        // Показываем обновленный список
                        if (!contacts.empty() && actionChoice != 4) {
                            std::cout << "========================================\n";
                            std::cout << "        ОБНОВЛЕННЫЙ СПИСОК\n";
                            std::cout << "========================================\n\n";
                            std::cout << "Всего записей: " << contacts.size() << "\n\n";

                            for (size_t i = 0; i < contacts.size(); ++i) {
                                std::cout << "Контакт #" << (i + 1) << ":\n";
                                contacts[i].display();
                                std::cout << "\n";
                            }
                        }
                    }

                } while (actionChoice != 4);
            }
            break;

        case 3:
            std::cout << "Выход из программы...\n";
            break;
        }

        default:
            std::cout << "Ошибка! Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
            break;
        }  

        if (choice != 3) {
            std::cout << "\n\nНажмите Enter для продолжения...";
            clearInputBuffer();
            std::cin.get();
            system("cls");
        }

    } while (choice != 3);  

    return 0;
} 